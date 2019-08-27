// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckForAmmo.generated.h"

/**
 * This service checks if the Bot need ammo.
 * If that's the case it updates the corresponding Blackboard Values
 */
UCLASS()
class BOTARENA_API UBTService_CheckForAmmo : public UBTService
{
	GENERATED_BODY()

protected:

	/*
	 * Executed every tick interval (which you can set from the Behavior Tree while have this particular service selected)
	 */
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
