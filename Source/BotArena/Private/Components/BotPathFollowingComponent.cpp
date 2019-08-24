// Fill out your copyright notice in the Description page of Project Settings.


#include "BotPathFollowingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavArea_Crouch.h"

void UBotPathFollowingComponent::SetMoveSegment(int32 SegmentStartIndex)
{
	Super::SetMoveSegment(SegmentStartIndex);

	if (CharacterMovementComp)
	{
		//Get the nav point and check if it has a crouch flag
		const FNavPathPoint& SegmentStart = Path->GetPathPoints()[SegmentStartIndex];
		if (FNavAreaHelper::HasCrouchFlag(SegmentStart))
		{
			CharacterMovementComp->bWantsToCrouch = true;
			CharacterMovementComp->Crouch();
			
			GLog->Log("I should crouch!");
		}
		else
		{
			CharacterMovementComp->bWantsToCrouch = false;
		}
	}
}

void UBotPathFollowingComponent::SetMovementComponent(UNavMovementComponent* MoveComp)
{
	Super::SetMovementComponent(MoveComp);
	CharacterMovementComp = Cast<UCharacterMovementComponent>(MoveComp);
	GLog->Log("set move comp called");
}
