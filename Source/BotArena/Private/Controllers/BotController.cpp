// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BotController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"

ABotController::ABotController()
{
	BlackboardKey_MoveLocation = FName("MoveLocation");
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
	
}

void ABotController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UBlackboardComponent* BlackboardComp = GetBlackboardComponent();
	if (!IsFollowingAPath() && BlackboardComp)
	{	
		BlackboardComp->SetValueAsVector(BlackboardKey_MoveLocation, GetPawn()->GetActorLocation() + GetPawn()->GetActorForwardVector()*1250.f);
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
