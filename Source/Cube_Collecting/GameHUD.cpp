// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "Components/ProgressBar.h"

void UGameHUD::SetHealth(float CurrentHealth, float MaxHealth)
{
	if (HealthBar)
	{
		//set the percent of the progress bar
		HealthBar->SetPercent(CurrentHealth / MaxHealth);

	}
}

float UGameHUD::CheckHealth()
{
	if (HealthBar)
	{
		float HealthPercent = HealthBar->GetPercent();
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("%f"), HealthPercent));
		return HealthPercent;
	}
	return -1.0f;
}

