// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BotController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"



ABotController::ABotController()
{
	//Keys init
	BlackboardKey_MoveLocation = FName("MoveLocation");

	//Create the AI perception component
	if (!GetPerceptionComponent())
	{
		PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(FName("PawnSensingComp"));

		if (PerceptionComp)
		{
			SetPerceptionComponent(*PerceptionComp);
		}
	}
	
}

void ABotController::OnPerceptionUpdated(const TArray<AActor*>& SensedActors)
{
	GLog->Log("On Perception updated!");

	GLog->Log("sensed actors list:");
	for (int32 i = 0; i < SensedActors.Num(); i++)
	{
		GLog->Log(SensedActors[i]->GetName());
	}
}

void ABotController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!BTAsset)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid BT Asset"));
		return;
	}

	RunBehaviorTree(BTAsset);
	if (GetPerceptionComponent())
	{
		GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &ABotController::OnPerceptionUpdated);
		UAISenseConfig_Sight* SightConfig = Cast<UAISenseConfig_Sight>(GetPerceptionComponent()->GetSenseConfig(UAISense::GetSenseID<UAISense_Sight>()));
		if (SightConfig) 
		{
			GLog->Log("valid sight cfg");
			SightConfig->DetectionByAffiliation.bDetectEnemies = true;
			SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
			SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		}
	}
}

void ABotController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UBlackboardComponent* BlackboardComp = GetBlackboardComponent();
	if (!IsFollowingAPath() && BlackboardComp)
	{	
		//BlackboardComp->SetValueAsVector(BlackboardKey_MoveLocation, GetPawn()->GetActorLocation() + GetPawn()->GetActorForwardVector()*1250.f);
		BlackboardComp->SetValueAsVector(BlackboardKey_MoveLocation, GetPawn()->GetActorLocation() + GetPawn()->GetActorRightVector()*-1250.f);
	}
}

//void ABotController::BeginPlay()
//{
//	Super::BeginPlay();
//
//	if (!BTAsset)
//	{
//		GLog->Log("invalid bt"); //warning here
//		return;
//	}
//
//}
