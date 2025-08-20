// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/StateTreeAIComponent.h"
#include "AIWorldPerceptionComponent.h"
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
	//Goals
	UFUNCTION(BlueprintCallable, Category = "AI|Goal")
	void AddGoal(const FGameplayTag& GoalTag);

	UFUNCTION(BlueprintCallable, Category = "AI|Goal")
	void RemoveGoal(const FGameplayTag& GoalTag);

	UFUNCTION(BlueprintCallable, Category = "AI|Goal")
	bool HasAllGoals(const FGameplayTagContainer& Goals) const { return ActiveGoals.HasAll(Goals); }

	//States
	UFUNCTION(BlueprintCallable, Category = "AI|State")
	void ChangeCurrentState(const FGameplayTag& NewState);
	UFUNCTION(BlueprintCallable, Category = "AI|State")
	FGameplayTag GetCurrentState() const { return CurrentState; }
	UFUNCTION(BlueprintCallable, Category = "AI|State")
	FGameplayTag GetOldState() const { return OldState; }
	
	UFUNCTION(BlueprintCallable)
	UStateTreeComponent* GetStateTreeComponent() const { return StateTreeComponent.Get(); }
	UFUNCTION(BlueprintCallable)
	UAIWorldPerceptionComponent* GetAIWorldPerceptionComponent() const { return AIPerceptionComp.Get(); }

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStateTreeAIComponent> StateTreeComponent;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBlackboardData> BlackboardAsset;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAIWorldPerceptionComponent> AIPerceptionComp;

private:
	FGameplayTagContainer ActiveGoals; // Goals that are currently active for this AI Controller
	FOnGoalAdded OnGoalAdded; // Delegate called when a goal is added
	FOnGoalRemoved OnGoalRemoved; // Delegate called when a goal is removed

	FGameplayTag CurrentState;
	FGameplayTag OldState;
};
