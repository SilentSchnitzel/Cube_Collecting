// Copyright Epic Games, Inc. All Rights Reserved.

#include "Cube_CollectingGameMode.h"
#include "Cube_CollectingCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Cube.h"
#include <Kismet/GameplayStatics.h>
#include "Actor_Spawner.h"
#include "MenuPlayerController.h"
#include "MenuHUD.h"

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

	PlayerControllerClass = AMenuPlayerController::StaticClass();
	HUDClass = AMenuHUD::StaticClass();
}

void ACube_CollectingGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	bool spawn_cube = true;
	if (ACube_CollectingGameMode::check_cube() == false)
	{
		spawn_cube = true;
	}
	if (ACube_CollectingGameMode::check_cube() == true)
	{
		spawn_cube = false;
	}
	if (spawn_cube == true)
	{
		UWorld* world = GetWorld();
		AActor* ActorSpawnerTofind = UGameplayStatics::GetActorOfClass(world, AActor_Spawner::StaticClass());
		AActor_Spawner* ActorSpawnerReference = Cast<AActor_Spawner>(ActorSpawnerTofind);
		if (ActorSpawnerReference)
		{
			ActorSpawnerReference->Spawn();
		}
		else
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, TEXT("Error"));
			}
		}
		spawn_cube = false;
	}

}

bool ACube_CollectingGameMode::check_cube()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACube::StaticClass(), FoundActors);
	if (FoundActors.Num() == 0)
	{
		return false;
	}
	return true;
}
