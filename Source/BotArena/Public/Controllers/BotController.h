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

	/* Updates the percepted actors */
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& SensedActors);

	/* Time in seconds in which the target selection occured */
	float TimeSinceTargetSelection;

public:

	ABotController();

	/*
	 * Returns the world location of the selected target.
	 * If we haven't selected a target it will return the forward vector
	 */
	FVector GetSelectedTargetLocation() const;

	/* Updates the blackboard value with the provided location */
	void SetMoveToLocation(const FVector& Location);

	/* Updates the blackboard value with the provided ammo box */
	void SetAmmoBox(class AAmmoBox* AmmoBox);

	/* Returns a reference of the behavior tree asset */
	FORCEINLINE UBehaviorTree* GetCurrentTree() { return BTAsset; }

	/* Returns a reference of the enemy target that the controlled bot has currently selected */
	FORCEINLINE AActor* GetSelectedTarget() const;

	/* This should be called when the bot is at Low HP and wishes to retreat */
	void InitiateRetreat();

	/* In case the bot need ammo, set this to true to enable the search for ammo boxes in-game */
	void SetCollectAmmoStatus(const bool& NewStatus);

protected:

	/* The assigned behavior tree */
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BTAsset;

	/* Blackboard key for MoveLocation*/
	UPROPERTY(VisibleAnywhere)
	FName BlackboardKey_MoveLocation;

	/* Blackboard key for Selected Target*/
	UPROPERTY(VisibleAnywhere)
	FName BlackboardKey_SelectedTarget;

	/* Blackboard key for Should Retreat*/
	UPROPERTY(VisibleAnywhere)
	FName BlackboardKey_ShouldRetreat;

	/* Blackboard key for CollectAmmo */
	UPROPERTY(VisibleAnywhere)
	FName BlackboardKey_CollectAmmo;

	/* Blackboard key for Ammo Box Reference*/
	UPROPERTY(VisibleAnywhere)
	FName BlackboardKey_AmmoBox;

	/* Will only select target every X interval */
	UPROPERTY(EditDefaultsOnly)
	float SelectTargetInterval = 5.f;

	/* How fast the bot rotates to face a new target */
	UPROPERTY(EditAnywhere)
	float SelectTargetRotationSpeed = 1.f;

	/* The Perception component for this controller */
	UPROPERTY(VisibleAnywhere)
	class UAIPerceptionComponent* PerceptionComp;

	/* Should probably erase this on next iteration since its not used currently */
	UPROPERTY(VisibleAnywhere)
	class UAIPerceptionStimuliSourceComponent* StimuliSourceComp;

	/* The custom path following component */
	UPROPERTY(VisibleAnywhere)
	class UBotPathFollowingComponent* BotPathFollowingComp;

	/* Executes when we possess a new bot */
	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	virtual void OnUnPossess() override;
};
