// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CollectAmmo.generated.h"

/**
 * Searches for nearby Ammo Boxes in the area and updates the corresponding Blackboard values
 * Should probably rename this later on since its name is misleading
 */
UCLASS()
class BOTARENA_API UBTTask_CollectAmmo : public UBTTaskNode
{
	GENERATED_BODY()

	/*
	 * Executes the task when we have reached the node
	 */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
protected:

	/* The search radius the bot will try to find an ammo box */
	UPROPERTY(EditAnywhere)
	float SearchRadius = 600.f;


};
