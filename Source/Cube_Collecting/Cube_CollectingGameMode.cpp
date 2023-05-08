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
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACube_CollectingGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	static bool spawn_cube = true;
	if (spawn_cube == true)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, TEXT("hooray"));
		}
		spawn_cube = false;
	}
}

//things that this game mode has to do:
//1. track when to spawn cubes
//2. track when to teleport spawner
//3. track how much time the player has to find the cube*
//* = unsure of whether that is going to be a feature