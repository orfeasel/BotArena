// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ShootTarget.h"
#include "Tasks/AITask_RunEQS.h"
#include "AIController.h"
#include "Characters/AICharacter.h"
#include "BotController.h"
#include "BehaviorTree/Tasks/BTTask_RunEQSQuery.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Tasks/AITask.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

UBTTask_ShootTarget::UBTTask_ShootTarget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_ShootTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FireTime = 0.f;
	
	AAICharacter* Bot = Cast<AAICharacter>(OwnerComp.GetAIOwner()->GetCharacter());
	
	if (Bot)
	{
		Bot->FireWeapon();
		//bDelayCompleted = false;
		////FireTime = 0.f;
		//if (bDelayCompleted)
		//{
		//	return EBTNodeResult::Succeeded;
		//}
		//FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
		FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
		return EBTNodeResult::InProgress;
		
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;

}

void UBTTask_ShootTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	//GLog->Log("tick task");
	FireTime += DeltaSeconds;

	if (FireTime >= FireWeaponDelay)
	{
		//bDelayCompleted = true;
		FireTime = 0.f;
		//GLog->Log("finishing latent task");
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}