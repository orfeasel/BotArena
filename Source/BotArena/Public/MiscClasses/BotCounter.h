// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AICharacter.h"
#include "BotCounter.generated.h"


/**
 * This class should be ideally moved to a game instance to achieve a singleton pattern.
 * For now, just place a single instance on the test level and leave it be
 */
UCLASS()
class BOTARENA_API ABotCounter : public AActor
{
	GENERATED_BODY()

private:

	int32 Blue_Bots; //Team 1
	int32 Red_Bots;  //Team 2

	
public:	
	// Sets default values for this actor's properties
	ABotCounter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* Returns the number of blue bots */
	UFUNCTION(BlueprintCallable, Category=Misc)
	int32 GetBlueBotsCount() const { return Blue_Bots; }

	/* Returns the number of red bots */
	UFUNCTION(BlueprintCallable, Category = Misc)
	int32 GetRedBotsCount() const { return Red_Bots; }

	/* Updates the corresponding bot counters */
	UFUNCTION(BlueprintCallable, Category = Misc)
	void OnBotSpawn(ETeam BotTeam);

	/* Updates the corresponding bot counters */
	void OnBotDeath(ETeam BotTeam);

};
