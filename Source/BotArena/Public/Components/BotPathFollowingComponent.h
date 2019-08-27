// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navigation/PathFollowingComponent.h"
#include "BotPathFollowingComponent.generated.h"

/**
 * This custom path following component is expanding the default path following component and its
 * sole use in this project (for the time being) is to identify if the bot is currently standing
 * in an area that can crouch
 */
UCLASS()
class BOTARENA_API UBotPathFollowingComponent : public UPathFollowingComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(transient)
	class UCharacterMovementComponent* CharacterMovementComp;
	
public:

	/** Sets variables related to current move segment */
	virtual void SetMoveSegment(int32 SegmentStartIndex) override;

	/* Stores a movement comp ref for later use */
	virtual void SetMovementComponent(UNavMovementComponent* MoveComp) override;
	
	
};
