// Fill out your copyright notice in the Description page of Project Settings.


#include "SCCMWidget.h"
#include "SlateOptMacros.h"

#define LOCTEXT_NAMESPACE "FCCMContentTestModule"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SCCMWidget::Construct(const FArguments& InArgs)
{
	
    ChildSlot
        [
            SNew(SVerticalBox)
                +SVerticalBox::Slot()
                .Padding(10, 10)
                .MaxHeight(30)
                [
                    SNew(SHorizontalBox)

                        + SHorizontalBox::Slot()
                        .MaxWidth(100)
                        .VAlign(VAlign_Center)
                        [
                            SNew(STextBlock)
                                .Text(FText::FromString(TEXT("Output Path")))
                        ]

                        + SHorizontalBox::Slot()
                        [
                            SNew(SEditableTextBox)
                                .Text(FText::FromString("/CCM/FlatColours/"))
                                .HintText(LOCTEXT("CM_PathName_Label", "Please Provide a Path"))
                                .OnTextCommitted(this, &SCCMWidget::SetOutputPath)
                        ]

                        + SHorizontalBox::Slot()
                        .MaxWidth(200)
                        .VAlign(VAlign_Center)
                        [
                            SNew(STextBlock)
                                .Text(FText::FromString(TEXT("Colour Name")))
                        ]
                        + SHorizontalBox::Slot()
                        [
                            SNew(SEditableTextBox)
                                .Text(FText::FromString(TEXT("")))
                                .HintText(LOCTEXT("CM_ColourName_Label", "Please Provide a Unique Colour Name"))
                                .OnTextCommitted(this, &SCCMWidget::SetColourName)
                        ]
                ]
            + SVerticalBox::Slot()
                .Padding(FMargin(10, 10))
                [
                    SNew(STextBlock)
                        .Text(this, &SCCMWidget::DisplayErrors)
                ]
        ];
	
}

FText SCCMWidget::DisplayErrors() const
{
	return FText::FromString(ErrorMessage);
}

void SCCMWidget::SetColourName(const FText& Text, ETextCommit::Type CommitType)
{
    ErrorMessage = Text.ToString();
}

void SCCMWidget::SetOutputPath(const FText& Text, ETextCommit::Type CommitType)
{
    OutputPath = Text.ToString();
    ErrorMessage = OutputPath;
}



END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE