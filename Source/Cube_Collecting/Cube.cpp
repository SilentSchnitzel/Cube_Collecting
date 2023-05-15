// Fill out your copyright notice in the Description page of Project Settings.


#include "Cube.h"
#include "Engine/Blueprint.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"

// Sets default values
ACube::ACube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ACube::animation();
	ACube::detect_collisions();

}

void ACube::animation()
{
	static int counter = 0;
	counter++;

	FRotator NewRotation = FRotator(0.0f, (float)counter, 0.0f);
	
	SetActorRotation(NewRotation);
}

//Game/ThirdPerson/Blueprints/MyCube.MyCube
void ACube::detect_collisions()
{
	/*UBlueprint* Blueprint = LoadObject<UBlueprint>(nullptr, TEXT("Blueprint'Game/ThirdPerson/Blueprints/MyCube.MyCube'"));
	if (!Blueprint)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Error"));
		}
		return;
	}*/
	
	UBoxComponent* CollisionBox;
	CollisionBox = Cast<UBoxComponent>(FindComponentByClass<UBoxComponent>());
	if (!CollisionBox)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("of course this would not work"));
		return;
	}
}
void ACube::collision_handler()
{

}


