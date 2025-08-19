// Copyright Epic Games, Inc. All Rights Reserved.

#include "DiesIraeGameMode.h"
#include "DiesIraeCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADiesIraeGameMode::ADiesIraeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
