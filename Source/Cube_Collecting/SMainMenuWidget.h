// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "SlateBasics.h"
#include "SlateExtras.h"

#include "MenuHUD.h"
/**
 * 
 */
//line 17:
//way of passing information to the HUD
//passes in the MenuHUD class to the menu widget
class SMainMenuWidget : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SMainMenuWidget) {}

	SLATE_ARGUMENT(TWeakObjectPtr<AMenuHUD>, OwningHUD)

	SLATE_END_ARGS()

	//construction function for the widget
	void Construct(const FArguments& InArgs);

	FReply OnPlayClicked() const;
	FReply OnQuitClicked() const;

	//HUD that created this widget
	//does not count as a reference because it is a weak pointer
	TWeakObjectPtr<AMenuHUD> OwningHUD;

	//ensures that you can focus a widget, if you do not do this and try to focus a widget-
	//then an error pops up
	virtual bool SupportsKeyboardFocus() const override { return true; };
};
