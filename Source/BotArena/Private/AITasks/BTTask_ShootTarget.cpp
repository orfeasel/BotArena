// Fill out your copyright notice in the Description page of Project Settings.


#include "AITasks/BTTask_ShootTarget.h"
#include "AIController.h"
#include "Characters/AICharacter.h"
#include "BehaviorTree/Tasks/BTTask_RunEQSQuery.h"
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
		Bot->FireWeapon();
		return EBTNodeResult::Succeeded;
		
	}
	return EBTNodeResult::Failed;

}