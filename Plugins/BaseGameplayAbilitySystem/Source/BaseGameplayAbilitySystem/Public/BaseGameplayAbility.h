// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BaseGameplayAbility.generated.h"

/**
 *
 */
UENUM(BlueprintType)
enum class EBaseAbilityInputID : uint8
{
	// 0 None
	None			UMETA(DisplayName = "None"),
	// 1 Confirm
	Confirm			UMETA(DisplayName = "Confirm"),
	// 2 Cancel
	Cancel			UMETA(DisplayName = "Cancel"),
	// 3 LMB
	Ability1		UMETA(DisplayName = "Ability1"),
	// 4 RMB
	Ability2		UMETA(DisplayName = "Ability2"),
	// 5 Q
	Ability3		UMETA(DisplayName = "Ability3"),
	// 6 E
	Ability4		UMETA(DisplayName = "Ability4"),
	// 7 R
	Ability5		UMETA(DisplayName = "Ability5"),
	// 8 Sprint
	Sprint			UMETA(DisplayName = "Sprint"),
	// 9 Jump
	Jump			UMETA(DisplayName = "Jump")
};

USTRUCT(BlueprintType)
struct FAbilityCommitCostInfo
{
	GENERATED_BODY()

public:
	/*Usually the socket name the weapon attach to, but can also act as a misc param.
	* We use an ability source info data object to store these name and target actors
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability|Info")
	FName TargetId;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability|Info")
	TSubclassOf<UGameplayEffect> CostGameplayEffect;
};


UCLASS()
class BASEGAMEPLAYABILITYSYSTEM_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UBaseGameplayAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability|Info")
	FName AbilityName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability|Info")
	bool bAutoActivateOnGranted = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability|Cost")
	TArray<FAbilityCommitCostInfo> CommitCostInfo;

protected:
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	UFUNCTION(BlueprintCallable, Category = "Ability|Cost")
	virtual bool CommitAbilityCostOnExtraActor(bool BroadcastCommitEvent);
};