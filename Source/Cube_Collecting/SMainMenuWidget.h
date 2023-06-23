// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "SlateBasics.h"
#include "SlateExtras.h"

#include "MenuHUD.h"
/**
 * 
 */
class SMainMenuWidget : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SMainMenuWidget) {}

	SLATE_ARGUMENT(TWeakObjectPtr<AMenuHUD>, OwningHUD)

	SLATE_END_ARGS()

	//construction function for the widget
	void Construct(const FArguments& InArgs);

	//HUD that created this widget
	//does not count as a reference because it is a weak pointer
	TWeakObjectPtr<AMenuHUD> OwningHUD;

	virtual bool SupportsKeyboardFocus() const override { return true; };
};
