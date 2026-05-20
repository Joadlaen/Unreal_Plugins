// Fill out your copyright notice in the Description page of Project Settings.


#include "SCCMWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SCCMWidget::Construct(const FArguments& InArgs)
{
	
	ChildSlot
	[
		SNew(STextBlock)
			.Text(this, &SCCMWidget::TestWidget)
	];
	
}

FText SCCMWidget::TestWidget() const
{
	return FText::FromString(TEXT("Delegate Alive"));
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
