// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_Spawner.generated.h"

UCLASS()
class CUBE_COLLECTING_API AActor_Spawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AActor_Spawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* BoxVolume;
public: 
	UFUNCTION()
		void Spawn();

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AActor> ActorToSpawn;
};
