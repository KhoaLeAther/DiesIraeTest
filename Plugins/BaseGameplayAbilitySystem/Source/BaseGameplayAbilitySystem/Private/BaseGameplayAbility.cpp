// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameplayAbility.h"
#include "AbilitySystemGlobals.h"
#include "CustomData/AbilitySourceInfoDataObject.h"
#include "BaseGameplayAbilityTags.h"
#include "BaseAbilitySystemComponent.h"

UBaseGameplayAbility::UBaseGameplayAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	ActivationBlockedTags.AddTag(CharacterState::Dead);//TODO: refactor to a tags file
}

void UBaseGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (bAutoActivateOnGranted)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}

bool UBaseGameplayAbility::CommitAbilityCostOnExtraActor(bool BroadcastCommitEvent)
{
	if (UAbilitySystemGlobals::Get().ShouldIgnoreCosts())
		return true;
	if (CommitCostInfo.IsEmpty())
		return false;
	const FGameplayAbilitySpec* Spec = CurrentActorInfo->AbilitySystemComponent->FindAbilitySpecFromHandle(CurrentSpecHandle);
	if (!Spec)
		return false;
	UAbilitySourceInfoDataObject* SourceData = Cast<UAbilitySourceInfoDataObject>(Spec->SourceObject.Get());
	if (!IsValid(SourceData))
		return false;
	bool bResult = false;
	for (const auto& CostInfo : CommitCostInfo)
	{
		if (!SourceData->AbilityCostTargets.Contains(CostInfo.TargetId))
			continue;
		UGameplayEffect* CostGE = CostInfo.CostGameplayEffect->GetDefaultObject<UGameplayEffect>();
		if (!CostGE)
			continue;
		TWeakObjectPtr<AActor> SourceActor = SourceData->AbilityCostTargets.FindRef(CostInfo.TargetId);
		if (!SourceActor.IsValid())
			continue;
		const auto SourceGAS = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(SourceActor.Get());
		if (!SourceGAS)
			continue;
		// Last chance to fail (maybe we no longer have resources to commit since we after we started this ability activation)
		if (!CheckCost(CurrentSpecHandle, SourceGAS->AbilityActorInfo.Get()))
			continue;
		ApplyGameplayEffectToOwner(CurrentSpecHandle, SourceGAS->AbilityActorInfo.Get(), CurrentActivationInfo, CostGE, GetAbilityLevel(CurrentSpecHandle, CurrentActorInfo));
		bResult = true; //only one cost apply is enough
	}
	return bResult;
}