// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "Components/StaticMeshComponent.h"

#include "DrawDebugHelpers.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	WeaponSM = CreateDefaultSubobject<UStaticMeshComponent>(FName("WeaponSM"));

	//FAttachmentTransformRules WeaponAttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget,tr);
	WeaponSM->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget,true),FName("WeaponSocket"));
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

//void AAICharacter::AssignTeam_Implementation(ETeam NewTeam)
//{
//	Team = NewTeam;
//}

void AAICharacter::FireWeapon()
{
	ensure(WeaponSM);

	CurrentAmmo--;

	const UWorld* World = GetWorld();
	if (World)
	{
		FVector WeaponMuzzle = WeaponSM->GetSocketLocation(FName("BulletSocket"));
		FVector BulletEndLocation = WeaponMuzzle + GetActorForwardVector() * BulletRange;
		DrawDebugLine(World, WeaponMuzzle, BulletEndLocation, FColor::Blue, false, 15.f);
		DrawDebugPoint(World, WeaponMuzzle, 10.f, FColor::Black, false, 15.f);
		DrawDebugPoint(World, BulletEndLocation, 10.f, FColor::Red, false, 15.f);
		GLog->Log("fired weapon!");
	}

}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

