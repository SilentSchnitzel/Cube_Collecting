// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_Spawner.h"
#include "Components/BoxComponent.h"
#include "Cube.h"
#include "MySphere.h"
#include "GameFramework/Actor.h"


// Sets default values
AActor_Spawner::AActor_Spawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	BoxVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	BoxVolume->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


}

// Called when the game starts or when spawned
void AActor_Spawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActor_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//C: / Users / wtooy / Desktop / UnrealEngine / Cube_Collecting / Content / ThirdPerson / Blueprints / MyCube.uasset
void AActor_Spawner::Spawn()
{
	UClass* BlueprintActor = LoadClass<ACube>(nullptr, TEXT("/Game/ThirdPerson/Blueprints/MyCube.MyCube_C"));
	if (!BlueprintActor)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, TEXT("FAILED TO LOAD BLUEPRINT"));
		}
	}
	UWorld* world = GetWorld();
	FTransform SpawnTransform = GetActorTransform();
	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = this;
	if (world)
	{
		world->SpawnActor(BlueprintActor, &SpawnTransform, SpawnParam);
	}
}

void AActor_Spawner::Teleport()
{
}
