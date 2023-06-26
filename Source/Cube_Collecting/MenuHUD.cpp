// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHUD.h"
#include "SMainMenuWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"

void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine && GEngine->GameViewport)
	{
		//ensures that the widget knows about the HUD class -> lets the user access the world and do things
		//more specifically it creates a new instance of SMainMenuWidget and it sets the owning HUD to this which is a pointer top the current class
		MenuWidget = SNew(SMainMenuWidget).OwningHUD(this);
		//This line of code adds a widget the the viewport content, creates and assigns a weak widget to the menu widget container variable
		//(the SAssignNew Macro is used to create and assign something to a variable all in one step), PossiblyNullContent sets the of SWeakWidget
		//to the value of MenuWidget, and ToSharedRef creates a shared reference to the MenuWidget object allowing multiple parts of the code to refer to it
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(MenuWidgetContainer, SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef()));
	}
}
