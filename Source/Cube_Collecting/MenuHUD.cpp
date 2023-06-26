// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHUD.h"
#include "SMainMenuWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"
#include "GameFramework/HUD.h"
#include "GameFramework/PlayerController.h"

void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	ShowMenu();
}

void AMenuHUD::ShowMenu()
{
	if (GEngine && GEngine->GameViewport)
	{
		//ensures that the widget knows about the HUD class -> lets the user access the world and do things
		//more specifically it creates a new instance of SMainMenuWidget and it sets the owning HUD to this which is a pointer top the current class
		MenuWidget = SNew(SMainMenuWidget).OwningHUD(this);
		//This line of code adds a widget the the viewport content, creates and assigns a weak widget to the menu widget container variable
		//(the SAssignNew Macro is used to create and assign something to a variable all in one step), PossiblyNullContent sets the of SWeakWidget
		//to the value of MenuWidget, and ToSharedRef creates a shared reference to the MenuWidget object allowing multiple parts of the code to refer to it
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(MenuWidgetContainer, SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef()));
		if (PlayerOwner)
		{
			PlayerOwner->bShowMouseCursor = true;
			//the player is only allowed to interact with the UI until a button is pressed
			PlayerOwner->SetInputMode(FInputModeUIOnly());
		}
	}
}

void AMenuHUD::RemoveMenu()
{
	if (GEngine && GEngine->GameViewport && MenuWidget.IsValid() && MenuWidgetContainer.IsValid())
	{
		//this removes all widget content from the viewport
		GEngine->GameViewport->RemoveViewportWidgetContent(MenuWidgetContainer.ToSharedRef());

		if (PlayerOwner)
		{
			PlayerOwner->bShowMouseCursor = false;

			//sets the input focus to the game
			PlayerOwner->SetInputMode(FInputModeGameOnly());
		}
	}
}
