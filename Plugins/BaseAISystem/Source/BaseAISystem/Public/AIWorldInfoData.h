// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AIWorldInfoData.generated.h"

/**
 * 
 */
UCLASS(Abstract, DefaultToInstanced)
class BASEAISYSTEM_API UAIWorldInfoData : public UObject
{
	GENERATED_BODY()

public:
	virtual void UpdateWorldInfo() {}
};

UCLASS(Blueprintable)
class BASEAISYSTEM_API UAIWorldInfoData_Blueprint : public UAIWorldInfoData
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "AISystem|WorldInfo")
	void UpdateWorldInfo_BP();

public:
	void UpdateWorldInfo() override
	{
		UpdateWorldInfo_BP();
	}
};