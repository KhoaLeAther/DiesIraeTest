// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DiesIrae/DiesIraeCharacter.h"
#include "Interfaces/AISystemTaskInterface.h"
#include "AISystemTaskParameters.h"
#include "AISystemParameterComponent.h"
#include "DiesIraeCharacter_NPC.generated.h"

/**
 * 
 */
UCLASS()
class DIESIRAE_API ADiesIraeCharacter_NPC : public ADiesIraeCharacter, public IAISystemTaskInterface
{
	GENERATED_BODY()

	ADiesIraeCharacter_NPC(const class FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;

	UAISystemTaskParameters* GetTaskParameters(const FGameplayTag& State) const override;

	UFUNCTION(BlueprintCallable, Category = "Character|Attributes")
	float GetExpBounty() const;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAISystemParameterComponent> AISystemParameterComponent;
};
