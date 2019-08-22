// Fill out your copyright notice in the Description page of Project Settings.


#include "MiscClasses/Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Characters/AICharacter.h"

void AProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		AAICharacter* BotChar = Cast<AAICharacter>(OtherActor);
		if (BotChar)
		{
			BotChar->TakeDamage(Damage, FDamageEvent(), BotChar->GetController(), this);
			GLog->Log("bot took dmg");
			
		}
	}
	Destroy();
}

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileSM = CreateDefaultSubobject<UStaticMeshComponent>(FName("ProjectileSM"));
	
	if (ProjectileSM)
	{
		ProjectileSM->AttachToComponent(GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	}

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovementComp"));
	
}

void AProjectile::AdjustVelocity(const FVector& ProjectileTarget)
{
	//ProjectileMovementComp->Velocity = Velocity;

	FVector ProjectileTrajectory = ProjectileTarget - GetActorLocation();
	ProjectileTrajectory.Normalize();
	ProjectileMovementComp->Velocity = ProjectileTrajectory * VelocityMultiplier;
	ProjectileMovementComp->UpdateComponentVelocity();
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileSM->OnComponentHit.AddDynamic(this, &AProjectile::OnProjectileHit);
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

