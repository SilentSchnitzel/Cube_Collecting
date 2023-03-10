// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeSpawner.h"
#include "Components/BoxComponent.h"
#include "Cube.h"
#include "MySphere.h"

// Sets default values
ACubeSpawner::ACubeSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SpawnVolume->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


}

// Called when the game starts or when spawned
void ACubeSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubeSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubeSpawner::SpawnCube()
{
	//gets the location and rotation of the spawner
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();
	//gets the world
	UWorld* world = GetWorld();
	if (world) {
		world->SpawnActor<AMySphere>(SpawnLocation, SpawnRotation);
		
	}
}


