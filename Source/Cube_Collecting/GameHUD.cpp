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
