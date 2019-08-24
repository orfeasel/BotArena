// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/NavArea_Crouch.h"

UNavArea_Crouch::UNavArea_Crouch()
{
	DefaultCost = 0.f;
	FNavAreaHelper::Set(AreaFlags, ENavAreaFlag::Crouch);
	DrawColor = FColor::Blue;
}
