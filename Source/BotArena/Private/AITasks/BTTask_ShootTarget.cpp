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
	bNotifyTick = false;
}

EBTNodeResult::Type UBTTask_ShootTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAICharacter* Bot = Cast<AAICharacter>(OwnerComp.GetAIOwner()->GetCharacter());
	if (Bot)
	{
		//Fire the weapon and start ticking the task so we can add some delay to avoid
		//firing multiple times in the same tick event
		Bot->FireWeapon();
		return EBTNodeResult::Succeeded;
		
	}
	return EBTNodeResult::Failed;

}