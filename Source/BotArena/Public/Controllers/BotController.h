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

	/* Choose the closest target from the provided data */
	void SelectTarget(const TArray<AActor*>& TargetList);

	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& SensedActors);

	AActor* GetSelectedTarget() const;

	/* Time in seconds in which the target selection occured */
	float TimeSinceTargetSelection;

public:

	ABotController();

	/*
	 * Returns the world location of the selected target.
	 * If we haven't selected a target it will return the forward vector
	 */
	FVector GetSelectedTargetLocation() const;

protected:

	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BTAsset;

	UPROPERTY(VisibleAnywhere)
	FName BlackboardKey_MoveLocation;

	UPROPERTY(VisibleAnywhere)
	FName BlackboardKey_SelectedTarget;

	/* Will only select target if target is dead or last selected target was on the last tick of the interval */
	UPROPERTY(EditDefaultsOnly)
	float SelectTargetInterval = 5.f;

	UPROPERTY(VisibleAnywhere)
	class UAIPerceptionComponent* PerceptionComp;

	UPROPERTY(VisibleAnywhere)
	class UAIPerceptionStimuliSourceComponent* StimuliSourceComp;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;



	
	
};
