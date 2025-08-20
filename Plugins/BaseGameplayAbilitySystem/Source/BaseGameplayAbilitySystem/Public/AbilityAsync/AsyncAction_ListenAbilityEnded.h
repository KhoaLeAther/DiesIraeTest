// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/CancellableAsyncAction.h"
#include "AsyncAction_ListenAbilityEnded.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityEndDelegate, bool, bWasCancelled);

UCLASS(Blueprintable)
class BASEGAMEPLAYABILITYSYSTEM_API UAsyncAction_ListenAbilityEnded : public UCancellableAsyncAction
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, DisplayName = "Listen On Ability Ended", Category = "Sipher | Gameplay Abilities", meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", BlueprintInternalUseOnly = "TRUE"))
	static UAsyncAction_ListenAbilityEnded* ListenAbilityEnded(UObject* WorldContextObject, UAbilitySystemComponent* ASC, FGameplayAbilitySpecHandle SpecHandle);

protected:
	void OnAbilityEnd(const FAbilityEndedData& Data);
	virtual void Activate() override;
	virtual void Cancel() override;

protected:
	UPROPERTY(BlueprintAssignable, DisplayName = "On Ability Ended")
	FAbilityEndDelegate AbilityEndedDelegate;

	TWeakObjectPtr<UAbilitySystemComponent> WeakASC = nullptr;

	FGameplayAbilitySpecHandle SpecHandle;
};