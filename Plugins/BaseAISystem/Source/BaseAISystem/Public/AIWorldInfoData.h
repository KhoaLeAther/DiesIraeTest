// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIWorldInfoData.generated.h"

/**
 * 
 */
UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class BASEAISYSTEM_API UAIWorldInfoData : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AISystem | WorldInfo")
	FName BlackboardKeyName;//BB key name for this world data to update

	UPROPERTY(EditAnywhere, Category = "AISystem | WorldInfo")
	float UpdateInterval = 0.0f;

	TWeakObjectPtr<UBlackboardComponent> BlackboardComp;
	TWeakObjectPtr<APawn> OwnerPawn;

private:
	float RemainTime = 0.0f;

protected:
	virtual void UpdateWorldInfo() {}
	UFUNCTION(BlueprintCallable, Category = "AISystem | WorldInfo")
	UBlackboardComponent* GetBlackboardComponent() const
	{
		return BlackboardComp.Get();
	}
	UFUNCTION(BlueprintCallable, Category = "AISystem | WorldInfo")
	APawn* GetOwnerPawn() const
	{
		return OwnerPawn.Get();
	}

public:
	void SetBlackboardComponent(UBlackboardComponent* InBlackboardComp)
	{
		BlackboardComp = InBlackboardComp;
	}
	void SetOwnerPawn(APawn* InOwnerPawn)
	{
		OwnerPawn = InOwnerPawn;
	}
	void UpdateRemainingTime(float DeltaTime);
};

UCLASS(Abstract, Blueprintable)
class BASEAISYSTEM_API UAIWorldInfoData_Blueprint : public UAIWorldInfoData
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "AISystem|WorldInfo")
	void UpdateWorldInfo_BP();

	void UpdateWorldInfo() override
	{
		UpdateWorldInfo_BP();
	}
};