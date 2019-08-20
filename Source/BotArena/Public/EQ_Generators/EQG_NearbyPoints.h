// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/Generators/EnvQueryGenerator_ProjectedPoints.h"
#include "EQG_NearbyPoints.generated.h"

/**
 * 
 */
UCLASS()
class BOTARENA_API UEQG_NearbyPoints : public UEnvQueryGenerator_ProjectedPoints
{
	GENERATED_BODY()

	virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;

	/* The distance between each point of the same Angle */
	UPROPERTY(EditAnywhere, Category = NearbyPoints)
	float PointsDistance = 150.f;
	
	/* The gap of points that will NOT be generated in front of the character */
	UPROPERTY(EditAnywhere, Category = NearbyPoints)
	float DegreesGap = 60.f;

	/* Angle Step is the step that the angles increase. A small value means that more item will get generated */
	UPROPERTY(EditAnywhere, Category = NearbyPoints)
	float AngleStep = 20.f;

	/* The max range of our nearby points */
	UPROPERTY(EditAnywhere, Category = NearbyPoints)
	float MaxRange = 500.f;
};
