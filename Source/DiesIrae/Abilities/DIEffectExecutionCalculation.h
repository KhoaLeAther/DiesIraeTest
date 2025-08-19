// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "DIEffectExecutionCalculation.generated.h"

/**
 * 
 */
UCLASS()
class DIESIRAE_API UDIEffectExecutionCalculation_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

	UDIEffectExecutionCalculation_Damage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	
};
