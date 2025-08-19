// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DiesIrae/DiesIraeCharacter.h"
#include "DiesIraeCharacter_NPC.generated.h"

/**
 * 
 */
UCLASS()
class DIESIRAE_API ADiesIraeCharacter_NPC : public ADiesIraeCharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;

	UFUNCTION(BlueprintCallable, Category = "Character|Attributes")
	float GetExpBounty() const;
};
