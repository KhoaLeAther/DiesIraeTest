// Fill out your copyright notice in the Description page of Project Settings.


#include "DiesIrae/Characters/DiesIraeCharacter_NPC.h"

ADiesIraeCharacter_NPC::ADiesIraeCharacter_NPC(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Initialize the AI System Parameter Component
	AISystemParameterComponent = CreateDefaultSubobject<UAISystemParameterComponent>(TEXT("AISystemParameterComponent"));
}
void ADiesIraeCharacter_NPC::BeginPlay()
{
	Super::BeginPlay();
}

void ADiesIraeCharacter_NPC::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void ADiesIraeCharacter_NPC::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	InitializeAttributes(1);
}

UAISystemTaskParameters* ADiesIraeCharacter_NPC::GetTaskParameters(const FGameplayTag& State) const
{
	if (AISystemParameterComponent)
	{
		return AISystemParameterComponent->GetTaskParameters(State);
	}
	return nullptr;
}

float ADiesIraeCharacter_NPC::GetExpBounty() const
{
	if (CharacterAttributeSet)
	{
		return CharacterAttributeSet->GetExpBounty();
	}
	return 0.0f;
}
