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

private:

	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& SensedActors);

public:

	ABotController();

protected:

	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BTAsset;

	UPROPERTY(VisibleAnywhere)
	FName BlackboardKey_MoveLocation;

	UPROPERTY(VisibleAnywhere)
	class UAIPerceptionComponent* PerceptionComp;

	UPROPERTY(VisibleAnywhere)
	class UAIPerceptionStimuliSourceComponent* StimuliSourceComp;

	//virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

public:

	
	
};
