// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAbilitySystemComponent.h"

void UBaseAbilitySystemComponent::ReceiveDamage(UBaseAbilitySystemComponent* SourceASC, float TrueDmg, float ReducedDmg)
{
	ReceivedDmg.Broadcast(SourceASC, TrueDmg, ReducedDmg);
}

void UBaseAbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);
	TSubclassOf<UGameplayAbility> AbilityGranted = AbilitySpec.Ability.GetClass();
	OnAbilityGranted.Broadcast(AbilityGranted, AbilitySpec);
}

FGameplayEffectSpecHandle UBaseAbilitySystemComponent::MakeOutgoingSpecFromGE(UGameplayEffect* GE, float Level, FGameplayEffectContextHandle Context) const
{
	//SCOPE_CYCLE_COUNTER(STAT_GetOutgoingSpec);
	if (Context.IsValid() == false)
	{
		Context = MakeEffectContext();
	}
	FGameplayEffectSpec* NewSpec = new FGameplayEffectSpec(GE, Context, Level);
	return FGameplayEffectSpecHandle(NewSpec);
}
