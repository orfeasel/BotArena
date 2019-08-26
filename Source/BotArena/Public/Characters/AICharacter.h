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

	bool CanSeeSelectedTarget() const;

	/* Time since this character fired */
	float LastFireWeaponTime;

	/* True if the character can fire the weapon */
	bool CanFireWeapon() const;

	void DeactivateFireWeaponParticle();

public:
	// Sets default values for this character's properties
	AAICharacter();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	FORCEINLINE void AddAmmo(int32 Ammo) { CurrentAmmo += Ammo; }

	FORCEINLINE int32 GetCurrentAmmo() const { return CurrentAmmo; }

	/* Probably shouldn't hardcode this */
	FORCEINLINE bool LowOnAmmo() const { return CurrentAmmo < 10; }

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
	float Health;

	/* Max health of bots */
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth;

	/* Current Ammo of this bot */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CurrentAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* WeaponFireFX;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> ProjectileBP;

	/* By default while crouching the bot's mesh is falling below the ground so adjust its location to avoid this effect */
	UPROPERTY(EditAnywhere)
	FVector MeshCrouchAdjustLocation = FVector(0, 0, -70);

	/* If the bot is dead destroy it after X seconds */
	UPROPERTY(EditAnywhere)
	float DestroyActorDelay;

	/* 
	 * The health value that will trigger the retreat behavior.
	 * A value of 0.2 means that the bot will treat when its health is <= MaxHealth * RetreatHealthPercentage
	 */
	UPROPERTY(EditAnywhere,config,meta=(ClampMin="0.0", ClampMax="1.0"))
	float RetreatHealthPercentage;

	/* 
	 * Delay between successful FireWeapon() calls to avoid firing multiple times in the same tick
	 * Treat this as the weapon's "FireRate".
	 */
	UPROPERTY(EditDefaultsOnly)
	float FireDelay;

	/*
	 * Sad but true, I spent so much time configuring this particle that I just ended up
	 * deactivating after X seconds from the moment the bot fired to make the effect somewhat eye - friendly
	 */
	UPROPERTY(EditDefaultsOnly)
	float DeactivateParticleDelay;

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

	FORCEINLINE bool IsFriendly(const AAICharacter& OtherCharacter) const { return Team == OtherCharacter.Team; }

	FORCEINLINE bool IsHostile(const AAICharacter& OtherCharacter) const { return !IsFriendly(OtherCharacter); }

	FORCEINLINE ETeam GetTeam() const { return Team; }

	FORCEINLINE bool SameTeam(const AAICharacter& OtherCharacterr) const { return Team == OtherCharacterr.Team; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnConstruction(const FTransform& Transform) override;

};
