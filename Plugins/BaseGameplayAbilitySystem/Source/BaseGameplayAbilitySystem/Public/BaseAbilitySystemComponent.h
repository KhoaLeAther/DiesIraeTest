// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BaseAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReceivedDamageDelegate, UBaseAbilitySystemComponent*, SourceASC, float, InDmg, float, ReducedDmg);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGotGrantedAbility, TSubclassOf<UGameplayAbility>, AbilityGranted, FGameplayAbilitySpec, AbilitySpec);
/**
 *
 */
UCLASS()
class BASEGAMEPLAYABILITYSYSTEM_API UBaseAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	bool bAbilitiesGiven = false;

	FReceivedDamageDelegate ReceivedDmg;

	UPROPERTY(BlueprintAssignable, Category = "Ability")
	FGotGrantedAbility OnAbilityGranted;//in engine, click to ability component, then right click blueprint editor graph,
	//choose event of ability component/ability/onabilitygranted
	//this is use to bind event to when add an event (ex: active an infinite ability (passive ability) that come along only
	//with a certain ability - when that skill granted, check for event on ability granted return correct class, only if correct then we activate passive)

	virtual FGameplayEffectSpecHandle MakeOutgoingSpecFromGE(UGameplayEffect* GE, float Level, FGameplayEffectContextHandle Context) const;

	virtual void ReceiveDamage(UBaseAbilitySystemComponent* SourceASC, float TrueDmg, float ReducedDmg);

protected:
	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;//this is called in ability component->give ability

};
