// Fill out your copyright notice in the Description page of Project Settings.


#include "DiesIrae/Characters/DiesIraeCharacter_NPC.h"

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

float ADiesIraeCharacter_NPC::GetExpBounty() const
{
	if (CharacterAttributeSet)
	{
		return CharacterAttributeSet->GetExpBounty();
	}
	return 0.0f;
}
