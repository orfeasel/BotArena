// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EQC_GetSeeingTarget.generated.h"

/**
 * An EQS context that returns a reference of the SelectedTarget for a given bot.
 */
UCLASS()
class BOTARENA_API UEQC_GetSeeingTarget : public UEnvQueryContext
{
	GENERATED_BODY()


	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
};
