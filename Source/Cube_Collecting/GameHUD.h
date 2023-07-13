// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class CUBE_COLLECTING_API UGameHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	//update the HUD with the amount of health that the player currently has
	void SetHealth(float CurrentHealth, float MaxHealth);

	//display the player's health
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UProgressBar* HealthBar;
	
	float CheckHealth();
	
};
