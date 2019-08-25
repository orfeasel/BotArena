// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoBox.generated.h"

UCLASS()
class BOTARENA_API AAmmoBox : public AActor
{
	GENERATED_BODY()

private:

	//DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams( FComponentBeginOverlapSignature, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult &, SweepResult);

	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OveralappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:	
	// Sets default values for this actor's properties
	AAmmoBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, meta = (ClampMin = '1'))
	int32 MinAmmo = 1;

	UPROPERTY(EditAnywhere, meta = (ClampMin = '2'))
	int32 MaxAmmo = 2;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* AmmoBoxSM;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionBox;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
