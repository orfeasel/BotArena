// Fill out your copyright notice in the Description page of Project Settings.


#include "MiscClasses/BotCounter.h"

// Sets default values
ABotCounter::ABotCounter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABotCounter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABotCounter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABotCounter::OnBotSpawn(ETeam BotTeam)
{
	(BotTeam == ETeam::E_Team1) ? Blue_Bots++ : Red_Bots++;
}

void ABotCounter::OnBotDeath(ETeam BotTeam)
{
	(BotTeam == ETeam::E_Team1) ? Blue_Bots-- : Red_Bots--;
}

