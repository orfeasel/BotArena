// Fill out your copyright notice in the Description page of Project Settings.


#include "MiscClasses/AmmoBox.h"
#include "Components/BoxComponent.h"
#include "Characters/AICharacter.h"

void AAmmoBox::OnComponentBeginOverlap(UPrimitiveComponent* OveralappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AAICharacter* Bot = Cast<AAICharacter>(OtherActor);
		if(Bot)
		{
			Bot->AddAmmo(FMath::RandRange(MinAmmo, MaxAmmo));
			Destroy();
		}
	}
}

// Sets default values
AAmmoBox::AAmmoBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AmmoBoxSM = CreateDefaultSubobject<UStaticMeshComponent>(FName("AmmoBoxSM"));

	if (AmmoBoxSM)
	{
		SetRootComponent(AmmoBoxSM);
	}

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(FName("CollisionBox"));
	if (CollisionBox)
	{
		CollisionBox->AttachToComponent(AmmoBoxSM, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	}
	

}

// Called when the game starts or when spawned
void AAmmoBox::BeginPlay()
{
	Super::BeginPlay();

	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AAmmoBox::OnComponentBeginOverlap);
	}
	
}

// Called every frame
void AAmmoBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

