// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NavAreas/NavArea.h"
#include "NavMesh/NavMeshPath.h"
#include "NavArea_Crouch.generated.h"

/**
 * 
 */

UENUM()
namespace ENavAreaFlag
{
	enum Type
	{
		Default,
		Jump,
		Crouch
	};
}

namespace FNavAreaHelper
{
	FORCEINLINE bool IsSet(uint16 Flags, ENavAreaFlag::Type Bit) { return (Flags & (1 << Bit)) != 0; }
	FORCEINLINE void Set(uint16& Flags, ENavAreaFlag::Type Bit) { Flags |= (1 << Bit); }

	FORCEINLINE bool IsNavLink(const FNavPathPoint& PathVert) { return (FNavMeshNodeFlags(PathVert.Flags).PathFlags & RECAST_STRAIGHTPATH_OFFMESH_CONNECTION) != 0; }
	FORCEINLINE bool HasJumpFlag(const FNavPathPoint& PathVert) { return     IsSet(FNavMeshNodeFlags(PathVert.Flags).AreaFlags, ENavAreaFlag::Jump); }
	FORCEINLINE bool HasCrouchFlag(const FNavPathPoint& PathVert) { return IsSet(FNavMeshNodeFlags(PathVert.Flags).AreaFlags, ENavAreaFlag::Crouch); }
}

/*
 * Specifies a zone that the player can crouch ( place this near low height walls )
 * Thanks for this Mieszko!
 * https://wiki.unrealengine.com/index.php?title=Unreal_Engine_AI_Tutorial_-_1_-_Making_AI_Jump_as_a_Part_of_Path_Following
 */
UCLASS()
class BOTARENA_API UNavArea_Crouch : public UNavArea
{
	GENERATED_BODY()

	UNavArea_Crouch();

};
