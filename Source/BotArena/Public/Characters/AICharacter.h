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

	/* "Hacky" way to display the number of bots.
	 * Ideally this functionality should be wrapped in a singleton pattern (maybe on next iteration)
	 */
	class ABotCounter* BotCounterRef;

	/*
	 * Identifies is the bot can actually see the target or if the target is currently LOSing this instance
	 * @return true - if we can see the target, false otherwise
	 */
	bool CanSeeSelectedTarget() const;

	/* Time since this character fired */
	float LastFireWeaponTime;

	/* True if the character can fire the weapon again */
	bool CanFireWeapon() const;

	/* Manually deactivate the Beam particle */
	void DeactivateFireWeaponParticle();

public:
	// Sets default values for this character's properties
	AAICharacter();

	/*
	 * Base Take Damage event that exists in Actor.h
	 * @see https://www.unrealengine.com/blog/damage-in-ue4
	 * @param DamageAmount		How much damage to apply
	 * @param DamageEvent		Data package that fully describes the damage received.
	 * @param EventInstigator	The Controller responsible for the damage.
	 * @param DamageCauser		The Actor that directly caused the damage (e.g. the projectile that exploded, the rock that landed on you)
	 * @return					The amount of damage actually applied.
	 */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	/* Adds the given amount of ammo to this bot */
	FORCEINLINE void AddAmmo(int32 Ammo) { CurrentAmmo += Ammo; }

	/* Get the current ammo of this bot */
	FORCEINLINE int32 GetCurrentAmmo() const { return CurrentAmmo; }

	/* 
	 * Probably shouldn't hardcode this 
	 */
	FORCEINLINE bool LowOnAmmo() const { return CurrentAmmo < 10; }

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* The static mesh of the weapon */
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

	/* The beam particle that is activated every time the bot fires its weapon */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* WeaponFireFX;

	/* Sub class of the projectile actor class.
	 * Create a Blueprint based on this class and assign it here
	 */
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

	/* Returns true if the bot is currently alive */
	FORCEINLINE bool IsAlive() const { return Health > 0; }

	/* Attempts to fire 
	 * There are several rules that need to apply before we actually fire, such as:
	 * 1) A valid target must exist who is not LOSing this bot.
	 * 2) We need to have ammo before firing
	 * 3) The bot must be able to see the target who wishes to fire at
	 */
	UFUNCTION(BlueprintCallable,Category="BotArena")
	void FireWeapon();

	/* Returns true if the other bot is on the same team */
	FORCEINLINE bool IsFriendly(const AAICharacter& OtherCharacter) const { return Team == OtherCharacter.Team; }

	/* Return true if the other bot is on another team */
	FORCEINLINE bool IsHostile(const AAICharacter& OtherCharacter) const { return !IsFriendly(OtherCharacter); }

	/* Returns the current team of the bot */
	FORCEINLINE ETeam GetTeam() const { return Team; }

	/* Well this is the same as IsFriendly. Should probably pick one function on next iteration and stick with it. */
	FORCEINLINE bool SameTeam(const AAICharacter& OtherCharacterr) const { return Team == OtherCharacterr.Team; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* Since this is not a playable character this should be erased on next iteration */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* Construction script in the C++ side */
	virtual void OnConstruction(const FTransform& Transform) override;

};
