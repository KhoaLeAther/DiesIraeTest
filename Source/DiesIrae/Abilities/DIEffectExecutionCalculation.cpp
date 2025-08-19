// Fill out your copyright notice in the Description page of Project Settings.


#include "DiesIrae/Abilities/DIEffectExecutionCalculation.h"
#include "DiesIrae/Characters/AttributeSet/BaseCharacterAttributeSet.h"
#include "DiesIrae/Abilities/DiesIraeGameplayTags.h"

struct DIDamageStatics
{
	//DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);

	DIDamageStatics()
	{
		// Snapshot happens at time of GESpec creation

		// We're not capturing anything from the Source in this example, but there could be like AttackPower attributes that you might want.

		// Capture optional Damage set on the damage GE as a CalculationModifier under the ExecutionCalculation
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseCharacterAttributeSet, Damage, Source, true);

		// Capture the Target's Armor. Don't snapshot.
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UGDAttributeSetBase, Armor, Target, false);
	}
};

static const DIDamageStatics& DamageStatics()
{
	static DIDamageStatics DStatics;
	return DStatics;
}

UDIEffectExecutionCalculation_Damage::UDIEffectExecutionCalculation_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().DamageDef);
}

void UDIEffectExecutionCalculation_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetAvatarActor() : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	if (TargetTags->HasTag(Immunity::ImmuneDamage))
	{
		// If the target is immune to damage, we can skip the rest of the execution
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(FGameplayAttribute(UBaseAttributeSet::GetInDamageAttribute()),
			EGameplayModOp::Override, 0.f));
		return;
	}

	float Damage = 0.0f;
	// Capture optional damage value set on the damage GE as a CalculationModifier under the ExecutionCalculation
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DamageDef, EvaluationParameters, Damage);
	// Add SetByCaller damage if it exists
	Damage += FMath::Max<float>(Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), false, -1.0f), 0.0f);

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(FGameplayAttribute(UBaseAttributeSet::GetInDamageAttribute()),
		EGameplayModOp::Override, Damage));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(FGameplayAttribute(UBaseAttributeSet::GetHealthAttribute()),
		EGameplayModOp::Additive, -Damage));
}
