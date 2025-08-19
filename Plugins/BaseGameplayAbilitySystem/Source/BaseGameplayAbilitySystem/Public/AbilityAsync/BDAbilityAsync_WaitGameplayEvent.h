// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Async/AbilityAsync_WaitGameplayEvent.h"
#include "BDAbilityAsync_WaitGameplayEvent.generated.h"

/**
 * 
 */
UCLASS()
class BASEGAMEPLAYABILITYSYSTEM_API UBDAbilityAsync_WaitGameplayEvent : public UAbilityAsync_WaitGameplayEvent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Async", meta = (DefaultToSelf = "TargetActor"))
	static UBDAbilityAsync_WaitGameplayEvent* WaitGameplayEventSentToActor(AActor* TargetActor, FGameplayTag EventTag, bool OnlyTriggerOnce = false, bool OnlyMatchExact = true);

	virtual void Activate() override;
	virtual void EndAction() override;
};
