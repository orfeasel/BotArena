// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BotController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionTypes.h"
#include "Characters/AICharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BotPathFollowingComponent.h"
#include "MiscClasses/AmmoBox.h"

ABotController::ABotController()
{
	//Keys init
	BlackboardKey_MoveLocation = FName("MoveLocation");
	BlackboardKey_SelectedTarget = FName("SelectedTarget");
	BlackboardKey_ShouldRetreat = FName("ShouldRetreat");
	BlackboardKey_CollectAmmo = FName("CollectAmmo");
	BlackboardKey_AmmoBox = FName("AmmoBox");

	//Create the AI perception component
	if (!GetPerceptionComponent())
	{
		PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(FName("PawnSensingComp"));

		if (PerceptionComp)
		{
			SetPerceptionComponent(*PerceptionComp);
		}
	}

	//Initialise our custom path following comp. In beginplay make it as the default comp for our character's path following comp
	BotPathFollowingComp = CreateDefaultSubobject<UBotPathFollowingComponent>(FName("BotPathFollowingComponent"));
}

FVector ABotController::GetSelectedTargetLocation() const
{
	const UBlackboardComponent* BlackBoardComp = GetBlackboardComponent();
	if (BlackBoardComp)
	{
		UObject* Target = BlackBoardComp->GetValueAsObject(BlackboardKey_SelectedTarget);

		if (!Target) return FVector::ForwardVector;

		AActor* SelectedTarget = Cast<AActor>(Target);
		if (SelectedTarget)
		{
			return SelectedTarget->GetActorLocation();
		}
	}

	return FVector::ForwardVector;
}

void ABotController::SetMoveToLocation(const FVector& Location)
{
	ensure(GetBlackboardComponent());
	GetBlackboardComponent()->SetValueAsVector(BlackboardKey_MoveLocation, Location);
}

void ABotController::SetAmmoBox(AAmmoBox* AmmoBox)
{
	ensure(GetBlackboardComponent());
	GetBlackboardComponent()->SetValueAsObject(BlackboardKey_AmmoBox, AmmoBox);
}

void ABotController::InitiateRetreat()
{
	ensure(GetBlackboardComponent());
	GetBlackboardComponent()->SetValueAsBool(BlackboardKey_ShouldRetreat, true);
}

void ABotController::SetCollectAmmoStatus(const bool& NewStatus)
{
	ensure(GetBlackboardComponent());
	GetBlackboardComponent()->SetValueAsBool(BlackboardKey_CollectAmmo, NewStatus);
}

void ABotController::SelectTarget(const TArray<AActor*>& TargetList)
{
	ensure(GetBlackboardComponent());

	AAICharacter* ControlledCharacter = Cast<AAICharacter>(GetCharacter());

	if (!ControlledCharacter || TargetList.Num()<=0) return;

	//Choose the closest enemy bot
	if (!GetSelectedTarget() || TimeSinceTargetSelection>=SelectTargetInterval)
	{
		//Search for the closest target
		float ClosestDistance = 99999.f;
		AAICharacter* SelectedTarget = nullptr;
		FVector CharacterLocation = ControlledCharacter->GetActorLocation();

		//Choose a target
		for (int32 TargetIndex = 0; TargetIndex < TargetList.Num(); TargetIndex++)
		{
			//Only choose a single target from the available Bots
			AAICharacter* Bot = Cast<AAICharacter>(TargetList[TargetIndex]);
			if (Bot)
			{
				if (Bot->IsAlive() && ControlledCharacter->IsHostile(*Bot))
				{
					//We have a new target
					if ((Bot->GetActorLocation() - CharacterLocation).Size() < ClosestDistance)
					{
						ClosestDistance = (Bot->GetActorLocation() - CharacterLocation).Size();
						SelectedTarget = Bot;
						TimeSinceTargetSelection = 0.f;
						//GLog->Log("switched target!");
					}
				}
			}
		}
		//GLog->Log("selected target from sensed actors!");
		GetBlackboardComponent()->SetValueAsObject(BlackboardKey_SelectedTarget, SelectedTarget);
	}

}

void ABotController::OnPerceptionUpdated(const TArray<AActor*>& SensedActors)
{
	//GLog->Log("On Perception updated!");
	SelectTarget(SensedActors);

}

AActor* ABotController::GetSelectedTarget() const
{
	if (GetBlackboardComponent())
	{
		UObject* Target = GetBlackboardComponent()->GetValueAsObject(BlackboardKey_SelectedTarget);
		if (Target)
		{
			return Cast<AActor>(Target);
		}
	}
	return nullptr;
}

void ABotController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!BTAsset)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid BT Asset"));
		return;
	}

	//Execute the assigned behavior tree and set its sight config to identify all possible players
	RunBehaviorTree(BTAsset);
	if (GetPerceptionComponent())
	{
		GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &ABotController::OnPerceptionUpdated);
		UAISenseConfig_Sight* SightConfig = Cast<UAISenseConfig_Sight>(GetPerceptionComponent()->GetSenseConfig(UAISense::GetSenseID<UAISense_Sight>()));
		if (SightConfig) 
		{
			//GLog->Log("valid sight cfg");
			SightConfig->DetectionByAffiliation.bDetectEnemies = true;
			SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
			SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		}
	}
}

void ABotController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UBlackboardComponent* BlackBoardComp = GetBlackboardComponent();

	TimeSinceTargetSelection += DeltaTime;
	
	//If we have a valid target make sure to smoothly rotate so the bot can
	//face him every time
	if (BlackBoardComp)
	{
		UObject* SelectedTarget = BlackBoardComp->GetValueAsObject(BlackboardKey_SelectedTarget);

		if (SelectedTarget)
		{
			AActor* PossesedActor = GetCharacter();
			AActor* TargetToFace = Cast<AActor>(SelectedTarget);

			if (PossesedActor && TargetToFace)
			{
				FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(PossesedActor->GetActorLocation(), TargetToFace->GetActorLocation());
				PossesedActor->SetActorRotation(FMath::RInterpTo(PossesedActor->GetActorRotation(), TargetRotation, DeltaTime, SelectTargetRotationSpeed));
			}
		}

	}

}

void ABotController::BeginPlay()
{
	Super::BeginPlay();

	if (BotPathFollowingComp)
	{
		//For some reason this works fine inside begin play and not in the constructor.
		SetPathFollowingComponent(BotPathFollowingComp);
	}
}

void ABotController::OnUnPossess()
{
	Super::OnUnPossess();

	//By default the controller will stay in the level so manually destroy this actor
	Destroy();
}
