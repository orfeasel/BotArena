// Fill out your copyright notice in the Description page of Project Settings.


#include "EQ_Contexts/EQC_GetSeeingTarget.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Characters/AICharacter.h"
#include "Controllers/BotController.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void UEQC_GetSeeingTarget::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	UObject* QueryOwner = (QueryInstance.Owner).Get();
	if (QueryOwner)
	{
		AAICharacter* BotCharacter = Cast<AAICharacter>(QueryOwner);
		if (BotCharacter)
		{
			ABotController* BotController = Cast<ABotController>(BotCharacter->GetController());
			if (BotController)
			{
				//Provide the target in our context
				if (BotController->GetSelectedTarget())
				{
					UEnvQueryItemType_Actor::SetContextHelper(ContextData, BotController->GetSelectedTarget());
				}
				else
				{
					//LOS bot itself since we have no target
					UEnvQueryItemType_Actor::SetContextHelper(ContextData, BotCharacter);
				}
				
			}
		}
	}
}
