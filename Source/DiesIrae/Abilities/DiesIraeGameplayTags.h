// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "GameplayTags.h"
#include "DiesIraeGameplayTags.generated.h"

/**
 * 
 */
namespace Immunity
{
	DIESIRAE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(ImmuneDamage);
}

namespace SetByCaller
{
	DIESIRAE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SBC_Health);
	DIESIRAE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SBC_MaxHealth);
}

UCLASS()
class DIESIRAE_API UDiesIraeGameplayTags : public UObject
{
	GENERATED_BODY()
	
};
