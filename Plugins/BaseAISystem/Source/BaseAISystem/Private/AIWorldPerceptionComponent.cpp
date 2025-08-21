// Fill out your copyright notice in the Description page of Project Settings.


#include "AIWorldPerceptionComponent.h"
#include "AIController.h"

// Sets default values for this component's properties
UAIWorldPerceptionComponent::UAIWorldPerceptionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAIWorldPerceptionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAIWorldPerceptionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (const auto InfoData : WorldInfoPerceptions)
	{
		if (IsValid(InfoData))
			InfoData->UpdateRemainingTime(DeltaTime);
	}
	// ...
}

void UAIWorldPerceptionComponent::InitAllWorldInfoData(UBlackboardComponent* InBlackboardComp)
{
	BlackboardComp = InBlackboardComp;
	if (WorldInfoDataClasses.IsEmpty())
		return;
	for (const auto InfoClass : WorldInfoDataClasses)
	{
		if (UAIWorldInfoData* InfoData = NewObject<UAIWorldInfoData>(this, InfoClass))
			AddWorldInfoData(InfoData);
	}
}

void UAIWorldPerceptionComponent::SetUpWorldInfoData(UAIWorldInfoData* WorldInfoData)
{
	if (BlackboardComp.IsValid())
	{
		if (WorldInfoData)
		{
			WorldInfoData->SetBlackboardComponent(BlackboardComp.Get());
			if (const AAIController* AIController = Cast<AAIController>(GetOwner()))
			{
				WorldInfoData->SetOwnerPawn(AIController->GetPawn());
			}
		}
	}

}

void UAIWorldPerceptionComponent::AddWorldInfoData(UAIWorldInfoData* WorldInfoData)
{
	if (WorldInfoData)
	{
		WorldInfoPerceptions.Add(WorldInfoData);
		SetUpWorldInfoData(WorldInfoData);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("UAIWorldPerceptionComponent::AddWorldInfoData - WorldInfoData is null!"));
}

