// Fill out your copyright notice in the Description page of Project Settings.


#include "SCCMCalculatorInterface.h"
#include "SlateOptMacros.h"
#include "Widgets/Layout/SGridPanel.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Misc/DefaultValueHelper.h"
#include "SCCMFidgetWidget.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SCCMCalculatorInterface::Construct(const FArguments& InArgs)
{
    CurrentExpression = TEXT("");
	
	ChildSlot
	[
        SNew(SHorizontalBox)
            +SHorizontalBox::Slot()
            [
        SNew(SVerticalBox)
            
            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(10, 10)
            [
                SAssignNew(Display, STextBlock)
                    .Text(FText::FromString(CurrentExpression))
            ]

            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(10, 10)
            [
                SNew(SGridPanel)

                    // Row 0
                    + SGridPanel::Slot(0, 0)
                    [
                        SNew(SButton)
                            .Text(FText::FromString("7"))
                            .OnClicked(this, &SCCMCalculatorInterface::OnButtonClicked, FString("7"))
                    ]
                    + SGridPanel::Slot(1, 0)
                    [
                        SNew(SButton)
                            .Text(FText::FromString("8"))
                            .OnClicked(this, &SCCMCalculatorInterface::OnButtonClicked, FString("8"))
                    ]
                    + SGridPanel::Slot(2, 0)
                    [
                        SNew(SButton)
                            .Text(FText::FromString("9"))
                            .OnClicked(this, &SCCMCalculatorInterface::OnButtonClicked, FString("9"))
                    ]
                    + SGridPanel::Slot(3, 0)
                    [
                        SNew(SButton)
                            .Text(FText::FromString("/"))
                            .OnClicked(this, &SCCMCalculatorInterface::OnButtonClicked, FString("/"))
                    ]

                    // Row 1
                    + SGridPanel::Slot(0, 1)
                    [
                        SNew(SButton)
                            .Text(FText::FromString("4"))
                            .OnClicked(this, &SCCMCalculatorInterface::OnButtonClicked, FString("4"))
                    ]
                    + SGridPanel::Slot(1, 1)
                    [
                        SNew(SButton)
                            .Text(FText::FromString("5"))
                            .OnClicked(this, &SCCMCalculatorInterface::OnButtonClicked, FString("5"))
                    ]
                    + SGridPanel::Slot(2, 1)
                    [
                        SNew(SButton)
                            .Text(FText::FromString("6"))
                            .OnClicked(this, &SCCMCalculatorInterface::OnButtonClicked, FString("6"))
                    ]
                    + SGridPanel::Slot(3, 1)
                    [
                        SNew(SButton)
                            .Text(FText::FromString("*"))
                            .OnClicked(this, &SCCMCalculatorInterface::OnButtonClicked, FString("*"))
                    ]

                    // Row 2
                    + SGridPanel::Slot(0, 2)
                    [
                        SNew(SButton)
                            .Text(FText::FromString("1"))
                            .OnClicked(this, &SCCMCalculatorInterface::OnButtonClicked, FString("1"))
                    ]
                    + SGridPanel::Slot(1, 2)
                    [
                        SNew(SButton)
                            .Text(FText::FromString("2"))
                            .OnClicked(this, &SCCMCalculatorInterface::OnButtonClicked, FString("2"))
                    ]
                    + SGridPanel::Slot(2, 2)
                    [
                        SNew(SButton)
                            .Text(FText::FromString("3"))
                            .OnClicked(this, &SCCMCalculatorInterface::OnButtonClicked, FString("3"))
                    ]
                    + SGridPanel::Slot(3, 2)
                    [
                        SNew(SButton)
                            .Text(FText::FromString("-"))
                            .OnClicked(this, &SCCMCalculatorInterface::OnButtonClicked, FString("-"))
                    ]

                    // Row 3
                    + SGridPanel::Slot(0, 3)
                    [
                        SNew(SButton)
                            .Text(FText::FromString("0"))
                            .OnClicked(this, &SCCMCalculatorInterface::OnButtonClicked, FString("0"))
                    ]
                    + SGridPanel::Slot(1, 3)
                    [
                        SNew(SButton)
                            .Text(FText::FromString("C"))
                            .OnClicked(this, &SCCMCalculatorInterface::OnButtonClicked, FString("C"))
                    ]
                    + SGridPanel::Slot(2, 3)
                    [
                        SNew(SButton)
                            .Text(FText::FromString("="))
                            .OnClicked(this, &SCCMCalculatorInterface::OnButtonClicked, FString("="))
                    ]
                    + SGridPanel::Slot(3, 3)
                    [
                        SNew(SButton)
                            .Text(FText::FromString("+"))
                            .OnClicked(this, &SCCMCalculatorInterface::OnButtonClicked, FString("+"))
                    ]
                        + SGridPanel::Slot(1, 4)
                        [
                            SNew(SButton)
                                .Text(FText::FromString("."))
                                .OnClicked(this, &SCCMCalculatorInterface::OnButtonClicked, FString("."))
                        ]
                        + SGridPanel::Slot(2, 4)
                        [
                            SNew(SButton)
                                .Text(FText::FromString("DEL"))
                                .OnClicked(this, &SCCMCalculatorInterface::OnButtonClicked, FString("DEL"))
                        ]
            ]
            ]
            +SHorizontalBox::Slot()
                .Padding(10, 10)
                .VAlign(VAlign_Top)
                [
                    SNew(SVerticalBox)
                        + SVerticalBox::Slot()
                        .MaxHeight(30)
                        [
                            SNew(SEditableTextBox)
                                .Text(FText::FromString("Enter any notes here..."))
                        ]
                        
                        +SVerticalBox::Slot()
                        .Padding(10,10)
                        .VAlign(VAlign_Center)
                        [
                            SNew(SCCMFidgetWidget)
                        ]
                ]
	];
	
}



//END_SLATE_FUNCTION_BUILD_OPTIMIZATION





FReply SCCMCalculatorInterface::OnButtonClicked(FString Value)
{

    if (Value == "C")
    {
        CurrentExpression = "";
    }
    else if (Value == "DEL")
    {
        if (CurrentExpression.Len() > 0)
        {
            CurrentExpression = CurrentExpression.LeftChop(1);
        }
    }
    else if (Value == "=")
    {
        EvaluateExpression();
    }
    else
    {
        CurrentExpression += Value;
    }

    Display->SetText(FText::FromString(CurrentExpression));
    return FReply::Handled();
}
void SCCMCalculatorInterface::EvaluateExpression()
{
    double Result = 0.0;

    TCHAR OP = 0;
    int32 OpIndex = INDEX_NONE;

    for (int32 i = 0; i < CurrentExpression.Len(); i++)
    {
        if (CurrentExpression[i] == '+' || CurrentExpression[i] == '-' || CurrentExpression[i] == '*' || CurrentExpression[i] == '/')
        {
            OP = CurrentExpression[i];
            OpIndex = i;
            break;
        }
    }

    if (OpIndex != INDEX_NONE)
    {
        double A = FCString::Atof(*CurrentExpression.Left(OpIndex));
        double B = FCString::Atof(*CurrentExpression.Mid(OpIndex + 1));

        if (OP == '+')
        {
            Result = A + B;
        }
        else if (OP == '-')
        {
            Result = A - B;
        }
        else if (OP == '*')
        {
            Result = A * B;
        }
        else if (OP == '/')
        {
            if (B != 0)
            {
                Result = A / B;
            }
        }


        //switch (Op)
        //{
        //case '+': Result = A + B; break;
        //case '-': Result = A - B; break;
        //case '*': Result = A * B; break;
        //case '/': Result = B != 0 ? A / B : 0; break;
        //}

        CurrentExpression = FString::SanitizeFloat(Result);
    }
}
