// Fill out your copyright notice in the Description page of Project Settings.


#include "Cube.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Cube_CollectingCharacter.h"
#include "Engine/Engine.h"
#include "Actor_Spawner.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ACube::ACube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	CollisionBox->SetCollisionProfileName("Trigger");

	CollisionBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACube::OnOverlapBegin);

	//AActor_Spawner* spawner;
	//spawner = Cast<AActor_Spawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AActor_Spawner::StaticClass()));
	//spawner->Teleport();

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

	FRotator NewRotation = FRotator(0.0f, (float)counter, 0.0f);
	
	SetActorRotation(NewRotation);
}


void ACube::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACube_CollectingCharacter::StaticClass()))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("character touched cube"));
			this->Destroy();
		}
	}
}

