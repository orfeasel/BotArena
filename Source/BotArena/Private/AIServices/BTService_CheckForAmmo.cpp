// Fill out your copyright notice in the Description page of Project Settings.


#include "AIServices/BTService_CheckForAmmo.h"
#include "Characters/AICharacter.h"
#include "Controllers/BotController.h"

void UBTService_CheckForAmmo::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	
	ABotController* BotCon = Cast<ABotController>(OwnerComp.GetAIOwner());
	if (BotCon)
	{
		AAICharacter* Bot = Cast<AAICharacter>(BotCon->GetCharacter());
		
		if (Bot)
		{
			//GLog->Log("setting low on ammo");
			if (Bot->LowOnAmmo())
			{
				//GLog->Log("I need ammo: " + Bot->GetName());
				//GLog->Log("Current ammo count: " + FString::FromInt(Bot->GetCurrentAmmo()));
			}
			BotCon->SetCollectAmmoStatus(Bot->LowOnAmmo());
			/*if (BotCon)
			{
				GLog->Log("setting low on ammo");
				BotCon->SetCollectAmmoStatus(Bot->LowOnAmmo());
			}*/
		}
	}
}
