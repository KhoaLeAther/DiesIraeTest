// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Base.h"

AAIController_Base::AAIController_Base()
{
	// Initialize the StateTreeComponent
	StateTreeComponent = CreateDefaultSubobject<UStateTreeAIComponent>(TEXT("StateTreeComponent"));
	StateTreeComponent->SetStartLogicAutomatically(false);
}

void AAIController_Base::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UBlackboardComponent* BlackboardComp = Blackboard;
	UseBlackboard(BlackboardAsset, BlackboardComp);
	StateTreeComponent->StartLogic();
}

void AAIController_Base::AddGoal(const FGameplayTag& GoalTag)
{
	if (!ActiveGoals.HasTag(GoalTag))
	{
		ActiveGoals.AddTag(GoalTag);
		OnGoalAdded.Broadcast(GoalTag); // Notify listeners that a goal has been added
		// Optionally, you can trigger any event or logic when a goal is added
	}
}

void AAIController_Base::RemoveGoal(const FGameplayTag& GoalTag)
{
	if (ActiveGoals.HasTag(GoalTag))
	{
		ActiveGoals.RemoveTag(GoalTag);
		OnGoalRemoved.Broadcast(GoalTag); // Notify listeners that a goal has been removed
		// Optionally, you can trigger any event or logic when a goal is removed
	}
}
