// Copyright Epic Games, Inc. All Rights Reserved.

#include "Cube_CollectingGameMode.h"
#include "Cube_CollectingCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACube_CollectingGameMode::ACube_CollectingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
