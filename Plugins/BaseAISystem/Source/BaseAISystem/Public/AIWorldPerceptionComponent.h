// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIWorldInfoData.h"
#include "AIWorldPerceptionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASEAISYSTEM_API UAIWorldPerceptionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAIWorldPerceptionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InitAllWorldInfoData(UBlackboardComponent* InBlackboardComp);
	void SetUpWorldInfoData(UAIWorldInfoData* WorldInfoData);

	UFUNCTION(BlueprintCallable, Category = "AI | WorldInfo")
	void AddWorldInfoData(UAIWorldInfoData* WorldInfoData);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AISystem | WorldInfo")
	TArray<TSubclassOf<UAIWorldInfoData>> WorldInfoDataClasses; // Classes of world info data to be used

	UPROPERTY()
	TArray<UAIWorldInfoData*> WorldInfoPerceptions;
	TWeakObjectPtr<UBlackboardComponent> BlackboardComp;
};
