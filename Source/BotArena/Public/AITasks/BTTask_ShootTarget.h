// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Templates/SharedPointer.h"
#include "BTTask_ShootTarget.generated.h"

/**
 * 
 */
UCLASS(Meta=(DisplayName="Shoot Target C++"))
class BOTARENA_API UBTTask_ShootTarget : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UBTTask_ShootTarget(const FObjectInitializer& ObjectInitializer);

public:

	UPROPERTY(EditAnywhere)
	float FireWeaponDelay;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	//bool bDelayCompleted = false;
	float FireTime = -1.f;
};
