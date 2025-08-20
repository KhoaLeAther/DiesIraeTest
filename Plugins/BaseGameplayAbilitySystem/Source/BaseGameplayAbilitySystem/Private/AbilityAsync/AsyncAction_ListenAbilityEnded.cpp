// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityAsync/AsyncAction_ListenAbilityEnded.h"

#include "AbilitySystemComponent.h"

UAsyncAction_ListenAbilityEnded* UAsyncAction_ListenAbilityEnded::ListenAbilityEnded(UObject* WorldContextObject, UAbilitySystemComponent* ASC, FGameplayAbilitySpecHandle SpecHandle)
{
	UAsyncAction_ListenAbilityEnded* Action = NewObject<UAsyncAction_ListenAbilityEnded>(WorldContextObject);
	Action->SpecHandle = SpecHandle;
	Action->WeakASC = ASC;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UAsyncAction_ListenAbilityEnded::OnAbilityEnd(const FAbilityEndedData& Data)
{
	if (!ShouldBroadcastDelegates())
	{
		return;
	}

	if (Data.AbilitySpecHandle == SpecHandle)
	{
		AbilityEndedDelegate.Broadcast(Data.bWasCancelled);

		//Stop & cleanup async action
		Cancel();
	}
}

void UAsyncAction_ListenAbilityEnded::Activate()
{
	Super::Activate();

	if (!WeakASC.IsValid())
	{
		Cancel();
		return;
	}

	auto ASC = WeakASC.Get();
	ASC->OnAbilityEnded.AddUObject(this, &UAsyncAction_ListenAbilityEnded::OnAbilityEnd);
}

void UAsyncAction_ListenAbilityEnded::Cancel()
{
	SpecHandle = FGameplayAbilitySpecHandle();

	if (WeakASC.IsValid())
	{
		WeakASC.Get()->OnAbilityEnded.RemoveAll(this);
		WeakASC = nullptr;
	}

	Super::Cancel();
}
