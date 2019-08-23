// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EQC_FindAllyBots.generated.h"

/**
 * 
 */
UCLASS()
class BOTARENA_API UEQC_FindAllyBots : public UEnvQueryContext
{
	GENERATED_BODY()


	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
	

private:

	/**
	 * Checks if already have included the given actor in the trace
	 */
	bool AlreadyTracedActor(const TArray<AActor*>& TracedActors, const AActor& ActorToCheck) const;
};
