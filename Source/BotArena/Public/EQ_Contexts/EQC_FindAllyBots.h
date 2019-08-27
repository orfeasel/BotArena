// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EQC_FindAllyBots.generated.h"

/**
 * This was initially created to implement an avoidance functionality via EQS for bots
 * This is an inefficient way of dealing with the mentioned problem.
 * This class is deprecated and we're currently using the default RVO avoidance which is built-in the CharacterMovementComponent
 */
UCLASS(Deprecated, meta=(DeprecationMessage="See comments above the class declaration"))
class BOTARENA_API UDEPRECATED_UEQC_FindAllyBots : public UEnvQueryContext
{
	GENERATED_BODY()


	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
	

private:

	/**
	 * Checks if already have included the given actor in the trace
	 */
	bool AlreadyTracedActor(const TArray<AActor*>& TracedActors, const AActor& ActorToCheck) const;
};
