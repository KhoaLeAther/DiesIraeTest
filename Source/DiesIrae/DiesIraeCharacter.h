// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DiesIrae/Characters/AttributeSet/BaseCharacterAttributeSet.h"
#include "BaseAbilitySystemComponent.h"
#include "BaseGameplayAbility.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemInterface.h"
#include "Logging/LogMacros.h"
#include "DiesIraeCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ADiesIraeCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ADiesIraeCharacter(const class FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;

#pragma region "AbilitySystem"
	UPROPERTY()
	UBaseAbilitySystemComponent* CharacterAbilityComponent;

	//CharacterAttributes
	UPROPERTY()
	UBaseCharacterAttributeSet* CharacterAttributeSet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character|Attributes")
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	virtual void InitializeAttributes(int CharLevel = 1);

	UFUNCTION(BlueprintCallable, Category = "Character|Attributes")
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "Character|Attributes")
	float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category = "Character|Attributes")
	float GetDamage() const;

	virtual void SetHealth(float Health);

	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;
	FDelegateHandle DamageChangedDelegateHandle;
	FDelegateHandle InDamageChangedDelegateHandle;

	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void DamageChanged(const FOnAttributeChangeData& Data);
	virtual void InDamageChanged(const FOnAttributeChangeData& Data);

#pragma endregion

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "Character|State")
	bool IsAlive() const;

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Character|State")
	void Die();
	virtual void Die_Implementation();
};

