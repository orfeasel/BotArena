// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BotController.generated.h"

/**
 * 
 */
UCLASS()
class BOTARENA_API ABotController : public AAIController
{
	GENERATED_BODY()

public:

	ABotController();

protected:

	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BTAsset;

	UPROPERTY(VisibleAnywhere)
	FName BlackboardKey_MoveLocation;

	//virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;
	
};
