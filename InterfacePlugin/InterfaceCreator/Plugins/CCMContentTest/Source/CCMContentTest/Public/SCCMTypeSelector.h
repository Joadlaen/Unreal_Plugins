// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "EdGraphSchema_K2.h"

/**
 * 
 */
class CCMCONTENTTEST_API SCCMTypeSelector : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCCMTypeSelector)
	{}
        SLATE_ATTRIBUTE(FEdGraphPinType, CurrentType)
        SLATE_EVENT(FOnPinTypeChanged, OnTypeChanged)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};


class SCCMTypeSelector : public SCompoundWidget
{


    void Construct(const FArguments& InArgs);

private:
    TSharedRef<SWidget> GenerateMenu();
    FReply OnTypePicked(FName Category);

private:
    FEdGraphPinType SelectedType;
    TAttribute<FEdGraphPinType> CurrentType;
    FOnPinTypeChanged OnTypeChanged;
};
