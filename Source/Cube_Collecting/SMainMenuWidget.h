// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "MainHUD.h"

/**
 * 
 */
class CUBE_COLLECTING_API SMainMenuWidget : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SMainMenuWidget) {}

	SLATE_ARGUMENT(TWeakObjectPtr<AMainHUD>, OwningHUD)

	SLATE_END_ARGS()

	//construction function for the widget
	void Construct(const FArguments& InArgs);
	
	//HUD that created this widget
	//does not count as a reference because it is a weak pointer
	TWeakObjectPtr<AMainHUD> OwningHUD;

	virtual bool SupportsKeyboardFocus() const override { return true; };
};
