// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "EdGraphSchema_K2.h"

/**
 * 
 */
class CCMCONTENTTEST_API SCCMWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCCMWidget)
	{
		
		}

	SLATE_END_ARGS()

	DECLARE_DELEGATE_OneParam(FOnPinTypeChanged, const FEdGraphPinType&);



	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FString ErrorMessage;
	FString ColourName;
	FString OutputPath;
	FLinearColor ColourToCreate;


	FText DisplayErrors() const;
	void SetColourName(const FText& Text, ETextCommit::Type CommitType);
	void SetOutputPath(const FText& Text, ETextCommit::Type CommitType);
	void OnFolderPicked(const FString& NewPath);



	void SetRedColour(float newValue);
	void SetGreenColour(float newValue);
	void SetBlueColour(float newValue);
	FSlateColor FetchColour() const;
	FReply CreateMaterial();

private:
	TSharedRef<SWidget> GenerateMenu();
	FReply OnTypePicked(FName Category);

private:
	FEdGraphPinType SelectedType;
	TAttribute<FEdGraphPinType> CurrentType;
	FOnPinTypeChanged OnTypeChanged;
};
