// Fill out your copyright notice in the Description page of Project Settings.


#include "SMainMenuWidget.h"

void SMainMenuWidget::Construct(const FArguments& InArgs)
{

	const FMargin ContentPadding =  FMargin(300.0f, 300.0f);
	ChildSlot
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SImage)
				.ColorAndOpacity(FColor::Black)
			]
	+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(ContentPadding)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			[
				SNew(STextBlock)

			]
		]
		];
}
