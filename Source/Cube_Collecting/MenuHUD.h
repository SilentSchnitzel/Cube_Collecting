// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class CUBE_COLLECTING_API AMenuHUD : public AHUD
{
	GENERATED_BODY()

protected:
	//store a reference to the menu itself
	TSharedPtr<class SMainMenuWidget> MenuWidget;
	//container will be used to remove and add the menu to the screen
	TSharedPtr<class SWidget> MenuWidgetContainer;

	virtual void BeginPlay() override;
	
};
