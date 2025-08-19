// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AIController.h"
#include "GameplayTagContainer.h"
#include "GoalGenerator_Base.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum EGoalGeneratePeriodType : uint8
{
	RunOnce,
	Loop
};

UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class BASEAISYSTEM_API UGoalGenerator_Base : public UObject
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "AISystem|Goal")
	FGameplayTag Goal;

	UPROPERTY(EditAnywhere, Category = "AISystem|Goal")
	FGameplayTagContainer RequiredGoals;//Has to have all these goals to consider generating this goal

	UPROPERTY(EditAnywhere, Category = "AISystem|Goal")
	TEnumAsByte<EGoalGeneratePeriodType> RunType = EGoalGeneratePeriodType::Loop;

public:
	UFUNCTION(BlueprintCallable, Category = "AISystem|Goal")
	virtual bool CanGenerate(AActor* Pawn, AAIController* AIController) const { return true; } // Default implementation, can be overridden
	
	UFUNCTION(BlueprintCallable, Category = "AISystem|Goal")
	FGameplayTag GetGoal() const { return Goal; } // Returns the goal this generator is responsible for
	UFUNCTION(BlueprintCallable, Category = "AISystem|Goal")
	FGameplayTagContainer GetRequiredGoals() const { return RequiredGoals; } // Returns the required goals for this generator
	UFUNCTION(BlueprintCallable, Category = "AISystem|Goal")
	bool RunContinuously() const { return RunType == EGoalGeneratePeriodType::Loop; } // Returns true if this generator should run continuously
};

UCLASS(Abstract, Blueprintable)
class BASEAISYSTEM_API UGoalGenerator_Blueprint : public UGoalGenerator_Base
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "AISystem|Goal")
	bool CanGenerate_BP(AActor* Pawn, AAIController* AIController) const;

public:
	bool CanGenerate(AActor* Pawn, AAIController* AIController) const override
	{
		return CanGenerate_BP(Pawn, AIController);
	}
};
