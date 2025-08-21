// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "AISystemTaskParameters.h"
#include "AISystemTaskInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UAISystemTaskInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BASEAISYSTEM_API IAISystemTaskInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, Category = "AISystem|Task")
	virtual UAISystemTaskParameters* GetTaskParameters(const FGameplayTag& State) const { return nullptr; }
};
