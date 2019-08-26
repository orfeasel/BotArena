// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Controllers/BotController.h"
#include "Particles/ParticleSystemComponent.h"
#include "MiscClasses/Projectile.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "Environment/NavArea_Crouch.h"
#include "GameFramework/CharacterMovementComponent.h"

bool AAICharacter::CanFireWeapon() const
{
	return (Health>0) && (CurrentAmmo > 0) && (LastFireWeaponTime >= FireDelay);
}

void AAICharacter::DeactivateFireWeaponParticle()
{
	if (WeaponFireFX)
	{
		//WeaponFireFX->Deactivate();
		//WeaponFireFX->SetBeamEndPoint(0, FVector::ZeroVector);
		WeaponFireFX->SetBeamEndPoint(0, WeaponFireFX->GetComponentLocation());
		//WeaponFireFX->GetBeamSourcePoint()
		WeaponFireFX->DeactivaateNextTick();
	}
}

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Init properties
	MaxHealth = 100.f;
	Health = 100.f;
	CurrentAmmo = 30;
	BulletRange = 2000.f;
	MeshCrouchAdjustLocation = FVector(0, 0, -70);
	DestroyActorDelay = 5.f;
	FireDelay = 0.35f;
	RetreatHealthPercentage = 0.2f;
	DeactivateParticleDelay = 0.2f;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	WeaponSM = CreateDefaultSubobject<UStaticMeshComponent>(FName("WeaponSM"));
	
	WeaponFireFX = CreateDefaultSubobject<UParticleSystemComponent>(FName("FireWeaponFX"));
	if (WeaponFireFX)
	{
		WeaponFireFX->SetAutoActivate(false);
		WeaponFireFX->AttachToComponent(WeaponSM, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
		WeaponFireFX->SetWorldLocation(WeaponSM->GetSocketLocation("BulletSocket"));
	}
	
}

float AAICharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	Health -= Damage;
	//TODO:Play hit montage

	//Should we retreat?
	if (Health <= MaxHealth * RetreatHealthPercentage)
	{
		ABotController* BotController = Cast<ABotController>(GetController());
		if (BotController)
		{
			BotController->InitiateRetreat();
		}
	}

	//If true the bot is dead so enable ragdoll physics and unposses to stop all AI logic
	if (!IsAlive())
	{
		//If the bot was crouching while he died we need to uncrouch first otherwise we're going to see
		//"funny" ragdoll effects
		if (GetCharacterMovement() && GetCharacterMovement()->IsCrouching())
		{
			GetCharacterMovement()->UnCrouch();
		}

		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->SetCollisionProfileName(FName("Ragdoll"));
		GetMesh()->SetCollisionResponseToAllChannels(ECR_Block);

		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

		if (GetController())
		{
			GetController()->UnPossess();
		}

		//Destroy the in-game actor after a few seconds
		FTimerHandle DestroyBotTimer;
		FTimerDelegate DestroyActorDelegate;
		DestroyActorDelegate.BindLambda([&]()
		{
			Destroy();
		});
		GetWorld()->GetTimerManager().SetTimer(DestroyBotTimer, DestroyActorDelegate, DestroyActorDelay, false);
		
		//GLog->Log("bot is dead activating ragdoll");
	}

	return Damage;
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;

	if (WeaponSM)
	{
		WeaponSM->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName("WeaponSocket"));
	}
}

void AAICharacter::FireWeapon()
{
	ensure(WeaponSM);

	const UWorld* World = GetWorld();

	ABotController* BotController = Cast<ABotController>(GetController());

	if (World && BotController && BotController->GetSelectedTarget() && CanFireWeapon())
	{
		FVector WeaponMuzzle = WeaponSM->GetSocketLocation(FName("BulletSocket"));
		FVector BulletEndLocation;// = WeaponMuzzle + GetActorForwardVector() * BulletRange;

		if (BotController)
		{
			BulletEndLocation = BotController->GetSelectedTargetLocation();
		}
		else
		{
			BulletEndLocation = WeaponMuzzle + GetActorForwardVector() * BulletRange;
		}


		if (ProjectileBP && WeaponFireFX)
		{
			
			AProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, FTransform(WeaponMuzzle), FActorSpawnParameters());
			SpawnedProjectile->AdjustVelocity(BulletEndLocation);
			
			//Activate the particle and adjust its end point
			WeaponFireFX->Activate();
			WeaponFireFX->SetBeamEndPoint(0, BulletEndLocation);
		}

		//DrawDebugLine(World, WeaponMuzzle, BulletEndLocation, FColor::Blue, false, 15.f);
		//DrawDebugPoint(World, WeaponMuzzle, 10.f, FColor::Black, false, 15.f);
		//DrawDebugPoint(World, BulletEndLocation, 10.f, FColor::Red, false, 15.f);

		CurrentAmmo--;
		LastFireWeaponTime = 0.f;
	}

}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LastFireWeaponTime += DeltaTime;

	if (LastFireWeaponTime >= DeactivateParticleDelay)
	{
		DeactivateFireWeaponParticle();
	}

	if (GetCharacterMovement())
	{
		//Adjust the mesh height in order to avoid having half of the mesh under the ground.
		if (GetCharacterMovement()->IsCrouching())
		{
			GetMesh()->SetRelativeLocation(FVector(0, 0, -70.f), true, nullptr, ETeleportType::TeleportPhysics);
		}
	}

}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAICharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Health = MaxHealth;
}

