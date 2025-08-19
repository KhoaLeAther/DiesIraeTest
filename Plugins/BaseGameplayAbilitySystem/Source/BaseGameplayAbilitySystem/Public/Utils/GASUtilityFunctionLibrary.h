// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BaseAbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "CustomData/DamageDataInfo.h"
#include "GASUtilityFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class BASEGAMEPLAYABILITYSYSTEM_API UGASUtilityFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/*Used by actor that dont want to has ability comp like Trap, Pick up items*/
	UFUNCTION(BlueprintCallable, Category = "GAS|Utilities")
	static void SetByCallerFromGameEffect(AActor* Target, FGameplayTag CallerTag, 
		UGameplayEffect* GE, const float Magnitude);

	UFUNCTION(BlueprintCallable, Category = "GAS|Utilities")
	static UGameplayEffect* CreateSetByCallerAdditiveGameEffectForAttribute(FGameplayAttribute ModifyAttribute, FGameplayTag CallerTag);

	UFUNCTION(BlueprintCallable, Category = "GAS|Utilities")
	static UGameplayEffect* CreateImmuneGE(const FGameplayTag& AssetTag, const FGameplayTagContainer& ImmuneTags, float Duration);

	UFUNCTION(BlueprintCallable, Category = "GAS|Utilities")
	static void AddHitReactDataToEffectSpec(FGameplayEffectContextHandle EffectContext, FBDDamageInfo DamageInfo);

	UFUNCTION(BlueprintPure, Category = "Ability|EffectContext", Meta = (DisplayName = "GetHitReactData"))
	static FBDDamageInfo EffectContextGetHitReactData(const FGameplayEffectContextHandle& EffectContext);
};
