// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EQC_GetSeeingTarget.generated.h"

/**
 * 
 */
UCLASS()
class BOTARENA_API UEQC_GetSeeingTarget : public UEnvQueryContext
{
	GENERATED_BODY()


	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
};
