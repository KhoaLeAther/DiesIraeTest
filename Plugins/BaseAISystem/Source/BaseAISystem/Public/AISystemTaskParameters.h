// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "AISystemTaskParameters.generated.h"

/**
 * 
 */
UCLASS(DefaultToInstanced, EditInlineNew, Abstract, Blueprintable)
class BASEAISYSTEM_API UAISystemTaskParameters : public UObject
{
	GENERATED_BODY()
};

UCLASS(Blueprintable)
class BASEAISYSTEM_API UAISystemTaskParameters_Combat : public UAISystemTaskParameters
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MinAttackRange; // Minimum range for combat attacks
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxAttackRange; // Maximum range for combat attacks
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> CombatAbility; // The combat ability to use in this state
};