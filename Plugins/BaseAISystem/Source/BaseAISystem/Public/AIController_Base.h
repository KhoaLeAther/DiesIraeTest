// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/StateTreeAIComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "GameplayTagContainer.h"
#include "AIController_Base.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGoalAdded, const FGameplayTag& GoalTag);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGoalRemoved, const FGameplayTag& GoalTag);

UCLASS()
class BASEAISYSTEM_API AAIController_Base : public AAIController
{
	GENERATED_BODY()

	AAIController_Base();
	
protected:
	virtual void OnPossess(APawn* InPawn) override;

public:
	UFUNCTION(BlueprintCallable)
	void AddGoal(const FGameplayTag& GoalTag);

	UFUNCTION(BlueprintCallable)
	void RemoveGoal(const FGameplayTag& GoalTag);

	UFUNCTION(BlueprintCallable)
	bool HasAllGoals(const FGameplayTagContainer& Goals) const { return ActiveGoals.HasAll(Goals); }

	UFUNCTION(BlueprintCallable)
	UStateTreeComponent* GetStateTreeComponent() const { return StateTreeComponent.Get(); }

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStateTreeAIComponent> StateTreeComponent;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBlackboardData> BlackboardAsset;

	FGameplayTagContainer ActiveGoals; // Goals that are currently active for this AI Controller

	FOnGoalAdded OnGoalAdded; // Delegate called when a goal is added
	FOnGoalRemoved OnGoalRemoved; // Delegate called when a goal is removed
};
