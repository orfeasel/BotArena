// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{
	E_Team1 UMETA(DisplayName="Team 1"),
	E_Team2 UMETA(DisplayName ="Team 2"),
	E_Team3 UMETA(DisplayName="Team 3")
};

UCLASS()
class BOTARENA_API AAICharacter : public ACharacter
{
	GENERATED_BODY()
	

public:
	// Sets default values for this character's properties
	AAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* WeaponSM;

	UPROPERTY(VisibleAnywhere)
	ETeam Team;

public:	

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BotArena")
	void AssignTeam(ETeam NewTeam);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
