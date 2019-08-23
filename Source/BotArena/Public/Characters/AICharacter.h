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
	
private:

	/* Time since this character fired */
	float LastFireWeaponTime;

	/* True if the character can fire the weapon */
	bool CanFireWeapon() const;

public:
	// Sets default values for this character's properties
	AAICharacter();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* WeaponSM;

	/* The team of the current bot */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ETeam Team;

	/* Current Health of this bot */
	UPROPERTY(VisibleAnywhere)
	float Health = 100.f;

	/* Current Ammo of this bot */
	UPROPERTY(VisibleAnywhere)
	int32 CurrentAmmo = 30;

	/* Max range for bullets to travel */
	UPROPERTY(EditAnywhere)
	float BulletRange = 2000.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* WeaponFireFX;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> ProjectileBP;

	/* If the bot is dead destroy it after X seconds */
	UPROPERTY(EditAnywhere)
	float DestroyActorDelay = 5.f;

	/* 
	 * Delay between successful FireWeapon() calls to avoid firing multiple times in the same tick
	 * Treat this as the weapon's "FireRate".
	 */
	UPROPERTY(EditDefaultsOnly)
	float FireDelay = 0.35f;

public:	

	/* Assigns a new team to the bot. 
	 * Make sure to update the Team here as well
	 * Implemented in Blueprint to apply a material change so we can tell the difference between opposite teams faster
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "BotArena")
	void AssignTeam(ETeam NewTeam);

	FORCEINLINE bool IsAlive() const { return Health > 0; }

	UFUNCTION(BlueprintCallable,Category="BotArena")
	void FireWeapon();

	FORCEINLINE bool IsFriendly(const AAICharacter& OtherCharacter) { return Team == OtherCharacter.Team; }

	FORCEINLINE bool IsHostile(const AAICharacter& OtherCharacter) { return !IsFriendly(OtherCharacter); }

	FORCEINLINE ETeam GetTeam() const { return Team; }

	FORCEINLINE bool SameTeam(const AAICharacter& OtherCharacterr) { return Team == OtherCharacterr.Team; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
