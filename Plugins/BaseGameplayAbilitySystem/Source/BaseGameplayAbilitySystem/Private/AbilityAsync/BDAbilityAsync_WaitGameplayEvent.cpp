// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityAsync/BDAbilityAsync_WaitGameplayEvent.h"

UBDAbilityAsync_WaitGameplayEvent* UBDAbilityAsync_WaitGameplayEvent::WaitGameplayEventSentToActor(AActor* TargetActor, FGameplayTag EventTag, bool OnlyTriggerOnce, bool OnlyMatchExact)
{
	UBDAbilityAsync_WaitGameplayEvent* MyObj = NewObject<UBDAbilityAsync_WaitGameplayEvent>();
	MyObj->SetAbilityActor(TargetActor);
	MyObj->Tag = EventTag;
	MyObj->OnlyTriggerOnce = OnlyTriggerOnce;
	MyObj->OnlyMatchExact = OnlyMatchExact;
	return MyObj;
}

void UBDAbilityAsync_WaitGameplayEvent::Activate()
{
	Super::Activate();
}

void UBDAbilityAsync_WaitGameplayEvent::EndAction()
{
	Super::EndAction();
}
