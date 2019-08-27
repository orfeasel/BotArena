// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BOTARENA_API AProjectile : public AActor
{
	GENERATED_BODY()

private:

	/* Called when this projectile hits something */
	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	/* Calculates the required velocity to make the projectile travel from the spawned location to the provided target*/
	void AdjustVelocity(const FVector& ProjectileTarget);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Damage that this projectile does on collision */
	UPROPERTY(EditAnywhere)
	float Damage;

	/* A multiplier for the velocity value */
	UPROPERTY(EditAnywhere)
	float VelocityMultiplier;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ProjectileSM;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
