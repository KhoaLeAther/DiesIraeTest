// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AbilitySourceInfoDataObject.generated.h"

/**
 * 
 */
UCLASS()
class BASEGAMEPLAYABILITYSYSTEM_API UAbilitySourceInfoDataObject : public UObject
{
	GENERATED_BODY()

public:
	TMap<FName, TWeakObjectPtr<AActor>> AbilityCostTargets;
};
