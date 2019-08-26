// Fill out your copyright notice in the Description page of Project Settings.


#include "AITasks/BTTask_CollectAmmo.h"
#include "Characters/AICharacter.h"
#include "CollisionQueryParams.h"
#include "WorldCollision.h"
#include "Engine/World.h"
#include "MiscClasses/AmmoBox.h"
#include "Controllers/BotController.h"
#include "DrawDebugHelpers.h"

EBTNodeResult::Type UBTTask_CollectAmmo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AActor* Bot = OwnerComp.GetOwner();

	if (Bot)
	{
		FCollisionObjectQueryParams CollisionObjectParams = FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic);

		FCollisionShape CollisionShape = FCollisionShape();
		CollisionShape.ShapeType = ECollisionShape::Sphere;
		CollisionShape.SetSphere(SearchRadius);

		TArray<FHitResult> OutHits;

		ABotController* BotCon = Cast<ABotController>(OwnerComp.GetAIOwner());

		DrawDebugSphere(GetWorld(), ((Bot->GetActorLocation() + FVector(150.f) - Bot->GetActorLocation()) / 2) + Bot->GetActorLocation(), SearchRadius, 10, FColor::Green, true);

		if (GetWorld()->SweepMultiByObjectType(OutHits, Bot->GetActorLocation(), Bot->GetActorLocation() + FVector(150.f), FQuat(), CollisionObjectParams, CollisionShape) && BotCon)
		{
			for (int32 Hit = 0; Hit < OutHits.Num(); Hit++)
			{
				if (OutHits[Hit].GetActor() && Cast<AAmmoBox>(OutHits[Hit].GetActor()))
				{
					//GLog->Log("found an ammo box! updating location!");
					DrawDebugPoint(GetWorld(), OutHits[Hit].ImpactPoint, 25.f, FColor::Black, true);
					AAmmoBox* Box = Cast<AAmmoBox>(OutHits[Hit].GetActor());
					BotCon->SetAmmoBox(Box);

					return EBTNodeResult::Succeeded;
				}
			}
		}
	}

	return EBTNodeResult::Failed;
}
