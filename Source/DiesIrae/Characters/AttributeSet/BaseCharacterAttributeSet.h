// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BaseAttributeSet.h"
#include "BaseCharacterAttributeSet.generated.h"

/**
 *
 */
UCLASS()
class UBaseCharacterAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()

public:

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;//only triggered with instant gameplay effect, so for DoT it will be applying many instant effects
	//we can do that by set timer and send event to deal dmg after a set duration

	//Character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat|Level")
	FGameplayAttributeData Level{ 1 };
	ATTRIBUTE_ACCESSORS(UBaseCharacterAttributeSet, Level)

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat|Level")
	FGameplayAttributeData Exp;
	ATTRIBUTE_ACCESSORS(UBaseCharacterAttributeSet, Exp)

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat|Level")
	FGameplayAttributeData MaxExp;
	ATTRIBUTE_ACCESSORS(UBaseCharacterAttributeSet, MaxExp)

	//Enemy
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat|Level")
	FGameplayAttributeData ExpBounty;//Enemy drop Exp when defeated
	ATTRIBUTE_ACCESSORS(UBaseCharacterAttributeSet, ExpBounty)

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat|Damage")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UBaseCharacterAttributeSet, Damage)

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat|Speed")
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UBaseCharacterAttributeSet, Speed)

};
