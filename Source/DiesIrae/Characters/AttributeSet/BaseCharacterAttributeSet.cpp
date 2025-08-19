// Fill out your copyright notice in the Description page of Project Settings.


#include "DiesIrae/Characters/AttributeSet/BaseCharacterAttributeSet.h"
#include "CustomData/DamageDataInfo.h"
#include "Utils/GASUtilityFunctionLibrary.h"
#include "GameplayEffectExtension.h"


void UBaseCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	// If a Max value changes, adjust current to keep Current % of Current to Max
	/*if (Attribute == GetMaxDurabilityAttribute()) // GetMaxHealthAttribute comes from the Macros defined at the top of the header
	{

	}*/
}

void UBaseCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

}
