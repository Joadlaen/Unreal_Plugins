// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

/**
 * 
 */
class CCMCONTENTTEST_API SCCMCalculatorInterface : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCCMCalculatorInterface)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	FString CurrentExpression;
	TSharedPtr<class STextBlock> Display;

	FReply OnButtonClicked(FString Value);
	void EvaluateExpression();
};
