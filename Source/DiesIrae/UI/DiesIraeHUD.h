// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DiesIraeHUD.generated.h"

/**
 * 
 */
UCLASS()
class DIESIRAE_API UDiesIraeHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Function to initialize the HUD
	UFUNCTION(BlueprintImplementableEvent, Category = "DiesIrae|HUD")
	void InitializeHUD();
	// Function to update the HUD with player stats
	UFUNCTION(BlueprintImplementableEvent, Category = "DiesIrae|HUD")
	void UpdatePlayerHealth(float HealthPercent);
};
