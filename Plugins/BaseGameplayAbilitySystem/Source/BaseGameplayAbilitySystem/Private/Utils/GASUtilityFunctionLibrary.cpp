// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/GASUtilityFunctionLibrary.h"
#include "GameplayEffectComponents/ImmunityGameplayEffectComponent.h"
#include "GameplayEffectComponents/AssetTagsGameplayEffectComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "BaseAttributeSet.h"

void UGASUtilityFunctionLibrary::SetByCallerFromGameEffect(AActor* Target, FGameplayTag CallerTag,
	UGameplayEffect* GE, const float Magnitude)
{
	if (!Target) return;

	UBaseAbilitySystemComponent* ASC = Cast<UBaseAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target));
	if (!ASC) return;

	FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();

	FGameplayEffectSpecHandle EffectHandle = ASC->MakeOutgoingSpecFromGE(GE, 0, EffectContext);
	
	if (EffectHandle.IsValid())
	{
		EffectHandle = UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(EffectHandle, CallerTag, Magnitude);
		FActiveGameplayEffectHandle ActiveGEHandle = ASC->ApplyGameplayEffectSpecToSelf(*EffectHandle.Data.Get());
	}
}

UGameplayEffect* UGASUtilityFunctionLibrary::CreateSetByCallerAdditiveGameEffectForAttribute(FGameplayAttribute ModifyAttribute, FGameplayTag CallerTag)
{
	UGameplayEffect* GE = NewObject<UGameplayEffect>(GetTransientPackage());
	GE->DurationPolicy = EGameplayEffectDurationType::Instant;
	
	int32 NewModIdx = GE->Modifiers.Num();
	GE->Modifiers.SetNum(NewModIdx + 1);
	FGameplayModifierInfo& AttMod = GE->Modifiers[NewModIdx];
	FSetByCallerFloat SetByCaller = FSetByCallerFloat();
	SetByCaller.DataTag = CallerTag;
	AttMod.ModifierMagnitude = SetByCaller;
	AttMod.ModifierOp = EGameplayModOp::Additive;
	AttMod.Attribute = ModifyAttribute;

	return GE;
}

UGameplayEffect* UGASUtilityFunctionLibrary::CreateImmuneGE(const FGameplayTag& AssetTag, const FGameplayTagContainer& ImmuneTags, float Duration)
{
	UGameplayEffect* GE = NewObject<UGameplayEffect>(GetTransientPackage());
	GE->DurationPolicy = EGameplayEffectDurationType::HasDuration;
	GE->DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(Duration));//iframe  

	TObjectPtr<UAssetTagsGameplayEffectComponent> AssetTagComp = GE->AddComponent<UAssetTagsGameplayEffectComponent>();
	if (AssetTagComp)
	{
		FInheritedTagContainer TagContainer = AssetTagComp->GetConfiguredAssetTagChanges();
		TagContainer.AddTag(AssetTag);
		AssetTagComp->SetAndApplyAssetTagChanges(TagContainer);
	}

	TObjectPtr<UImmunityGameplayEffectComponent> ImmunityComp = GE->AddComponent<UImmunityGameplayEffectComponent>();
	if (ImmunityComp)
	{
		FGameplayEffectQuery Query = FGameplayEffectQuery::MakeQuery_MatchAnyEffectTags(ImmuneTags);
		ImmunityComp->ImmunityQueries.Add(Query);
	}

	return GE;
}

void UGASUtilityFunctionLibrary::AddHitReactDataToEffectSpec(FGameplayEffectContextHandle EffectContext, FBDDamageInfo DamageInfo)
{
	if (FGameplayEffectContext_HitReactData* Data = static_cast<FGameplayEffectContext_HitReactData*>(EffectContext.Get()))
	{
		if (Data)
			Data->AddDamageInfo(DamageInfo);
	}
}

FBDDamageInfo UGASUtilityFunctionLibrary::EffectContextGetHitReactData(const FGameplayEffectContextHandle& EffectContext)
{
	if (const FGameplayEffectContext_HitReactData* Data = static_cast<const FGameplayEffectContext_HitReactData*>(EffectContext.Get()))
	{
		if (Data)
			if (Data->GetDamageInfo())
				return *Data->GetDamageInfo();
	}
	return FBDDamageInfo();
}

