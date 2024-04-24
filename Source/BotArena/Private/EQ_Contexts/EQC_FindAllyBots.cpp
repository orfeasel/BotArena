// Fill out your copyright notice in the Description page of Project Settings.


#include "EQ_Contexts/EQC_FindAllyBots.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "Characters/AICharacter.h"
#include "CollisionQueryParams.h"
#include "WorldCollision.h"
#include "Engine/World.h"

#include "DrawDebugHelpers.h"

void UEQC_FindAllyBots::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	UObject* QueryOwner = (QueryInstance.Owner).Get();

	if (QueryOwner)
	{
		AAICharacter* OwnerActor = Cast<AAICharacter>(QueryOwner);

		if (OwnerActor)
		{
			ETeam CurrentTeam = OwnerActor->GetTeam();

			FCollisionObjectQueryParams CollisionObjectParams = FCollisionObjectQueryParams(ECC_Pawn);

			FCollisionShape CollisionShape = FCollisionShape();
			CollisionShape.ShapeType = ECollisionShape::Sphere;
			CollisionShape.SetSphere(350.f);

			TArray<FHitResult> OutHits;
			TArray<AActor*> AllyBots;
			
			/*DrawDebugSphere(GetWorld(), ((OwnerActor->GetActorLocation() + FVector(150.f) - OwnerActor->GetActorLocation()) / 2) + OwnerActor->GetActorLocation(), 350.f, 10, FColor::Green, true);*/

			//Perform a sweep for nearby bots
			if (GetWorld()->SweepMultiByObjectType(OutHits, OwnerActor->GetActorLocation(), OwnerActor->GetActorLocation()+FVector(150.f), FQuat(), CollisionObjectParams, CollisionShape))
			{
				for (int32 HitIndex = 0; HitIndex < OutHits.Num(); HitIndex++)
				{
					AAICharacter* HitActor = Cast<AAICharacter>(OutHits[HitIndex].GetActor());

					//Only include valid bots in our final contexts;
					//We want to exclude the actor that performs the query plus any duplicate actors
					if (HitActor && HitActor!=OwnerActor && 
						OwnerActor->SameTeam(*HitActor) && !AlreadyTracedActor(AllyBots,*HitActor))
					{
						AllyBots.Add(HitActor);
					}
				}
			}

			/*GLog->Log("ally bots found : " + FString::FromInt(AllyBots.Num() - 1));
			GLog->Log("ally bots of: " + OwnerActor->GetName());
			for (int32 i = 0; i < AllyBots.Num(); i++)
			{
				GLog->Log(AllyBots[i]->GetName());
			}*/

			//Include the bots we found on the previous sweep in our context
			UEnvQueryItemType_Actor::SetContextHelper(ContextData, AllyBots);

		}
		
	}

}

bool UEQC_FindAllyBots::AlreadyTracedActor(const TArray<AActor*>& TracedActors, const AActor& ActorToCheck) const
{
	for (int32 ActorIndex = 0; ActorIndex < TracedActors.Num(); ActorIndex++)
	{
		if (TracedActors[ActorIndex]->GetName() == ActorToCheck.GetName())
		{
			//GLog->Log("already traced this actor!");
			return true;
		}
	}
	return false;
}
