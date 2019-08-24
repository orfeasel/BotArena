// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/NavArea_Crouch.h"

UNavArea_Crouch::UNavArea_Crouch()
{
	GLog->Log("area nav helper was set to crouch");
	FNavAreaHelper::Set(AreaFlags, ENavAreaFlag::Crouch);
}
