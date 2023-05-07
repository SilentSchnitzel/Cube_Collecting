// Fill out your copyright notice in the Description page of Project Settings.


#include "Cube.h"

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

}

void ACube::animation()
{
	static int counter = 0;
	counter++;
	// Get the current rotation of the actor
	//FRotator CurrentRotation = GetActorRotation();

	FRotator NewRotation = FRotator(0.0f, (float)counter, 0.0f);
	//FRotator NewRotation = FRotator(0.0f, 45.0f, 0.0f); // for example, a 45 degree Yaw rotation
	if (GEngine)
	{
		if (counter == 2)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, TEXT("counter equals 2"));
		}
		if (counter == 3)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, TEXT("counter equals 3"));
	}
	
	SetActorRotation(NewRotation);
}

