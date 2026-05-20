// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class CCMCONTENTTEST_API SCCMWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCCMWidget)
	{}
	SLATE_END_ARGS()


	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FString ErrorMessage;
	FString OutputPath;

	FText DisplayErrors() const;
	void SetColourName(const FText& Text, ETextCommit::Type CommitType);
	void SetOutputPath(const FText& Text, ETextCommit::Type CommitType);

};
