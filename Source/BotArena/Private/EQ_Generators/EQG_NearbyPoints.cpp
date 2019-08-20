// Fill out your copyright notice in the Description page of Project Settings.


#include "EQ_Generators/EQG_NearbyPoints.h"

void UEQG_NearbyPoints::GenerateItems(FEnvQueryInstance& QueryInstance) const
{
	TArray<FNavLocation> LocationCandidates;

	AActor* AIPawn = Cast<AActor>((QueryInstance.Owner).Get());

	if (!AIPawn || AngleStep <= 0) return;

	FVector PawnLocation = AIPawn->GetActorLocation();
	FVector PawnForwardVector = AIPawn->GetActorForwardVector();

	for (float Angle = DegreesGap; Angle < 360-DegreesGap; Angle += AngleStep)
	{
		FVector RightVector = PawnForwardVector.RotateAngleAxis(Angle, FVector::UpVector);

		for (float Distance = PointsDistance; Distance < MaxRange; Distance += PointsDistance)
		{
			FNavLocation NavLocation = FNavLocation(PawnLocation + RightVector * Distance);
			LocationCandidates.Add(NavLocation);
		}

	}

	//int32 PointsGenerated = LocationCandidates.Num();

	ProjectAndFilterNavPoints(LocationCandidates, QueryInstance);
	StoreNavPoints(LocationCandidates, QueryInstance);
}
