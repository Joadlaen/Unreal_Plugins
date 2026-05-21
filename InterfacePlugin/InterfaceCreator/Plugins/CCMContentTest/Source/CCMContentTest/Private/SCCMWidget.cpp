// Fill out your copyright notice in the Description page of Project Settings.


#include "SCCMWidget.h"
#include "SlateOptMacros.h"
#include "Widgets/Input/SSpinbox.h"
#include "AssetToolsModule.h"
#include "Factories/MaterialInstanceConstantFactoryNew.h"
#include "Materials/MaterialInstanceConstant.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "EdGraphSchema_K2.h"

#include "SCCMTypeSelector.h"
#include "Widgets/Input/SComboButton.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

#define LOCTEXT_NAMESPACE "FCCMContentTestModule"




BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SCCMWidget::Construct(const FArguments& InArgs)
{


    ChildSlot
        [
            SNew(SVerticalBox)
                + SVerticalBox::Slot()
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
                .Padding(10, 10)
                [
                    SNew(STextBlock)
                        .Text(this, &SCCMWidget::DisplayErrors)
                ]
                + SVerticalBox::Slot()
                .MaxHeight(30)
                .Padding(10, 10)
                [
                    SNew(SHorizontalBox)
                        + SHorizontalBox::Slot()
                        .MaxWidth(150)
                        [
                            SNew(SSpinBox<float>)
                                .MinValue(0.0f)
                                .MaxValue(255.0f)
                                .MinSliderValue(0.0f)
                                .MaxSliderValue(255.0f)
                                .Delta(0.1f)
                                .OnValueChanged(this, &SCCMWidget::SetRedColour)
                        ]
                    + SHorizontalBox::Slot()
                        .MaxWidth(150)
                        [
                            SNew(SSpinBox<float>)
                                .MinValue(0.0f)
                                .MaxValue(255.0f)
                                .MinSliderValue(0.0f)
                                .MaxSliderValue(255.0f)
                                .Delta(0.1f)
                                .OnValueChanged(this, &SCCMWidget::SetGreenColour)
                        ]
                    + SHorizontalBox::Slot()
                        .MaxWidth(150)
                        [
                            SNew(SSpinBox<float>)
                                .MinValue(0.0f)
                                .MaxValue(255.0f)
                                .MinSliderValue(0.0f)
                                .MaxSliderValue(255.0f)
                                .Delta(0.1f)
                                .OnValueChanged(this, &SCCMWidget::SetBlueColour)
                        ]
                ]
            + SVerticalBox::Slot()
                .Padding(10, 10)
                .MaxHeight(30)
                [
                    SNew(SButton)
                        .Text(FText::FromString("Make New Material"))
                        .OnClicked(this, &SCCMWidget::CreateMaterial)
                ]

                + SVerticalBox::Slot()
                .Padding(10, 10)
    ];
}
     




FText SCCMWidget::DisplayErrors() const
{
	return FText::FromString(ErrorMessage);
}

void SCCMWidget::SetColourName(const FText& Text, ETextCommit::Type CommitType)
{
    ColourName = "MI_FC_" + Text.ToString();
    ColourName = ColourName.Replace(TEXT(" "), TEXT(""));
    ErrorMessage = ColourName;
}

void SCCMWidget::SetOutputPath(const FText& Text, ETextCommit::Type CommitType)
{
    OutputPath = Text.ToString();
    ErrorMessage = OutputPath;
}

void SCCMWidget::OnFolderPicked(const FString& NewPath)
{
    OutputPath = NewPath;
    ErrorMessage = OutputPath;
}

void SCCMWidget::SetRedColour(float newValue)
{
    ColourToCreate.R = newValue;
    ErrorMessage = ColourToCreate.ToString();
}

void SCCMWidget::SetGreenColour(float newValue)
{
    ColourToCreate.G = newValue;
    ErrorMessage = ColourToCreate.ToString();
}

void SCCMWidget::SetBlueColour(float newValue)
{
    ColourToCreate.B = newValue;
    ErrorMessage = ColourToCreate.ToString();
}

FSlateColor SCCMWidget::FetchColour() const
{
    return FSlateColor(ColourToCreate);
}




FReply SCCMWidget::CreateMaterial()
{
    FString BaseMaterialPath = TEXT("Material'/CCM/FlatColours/M_FlatColour.M_FlatColour'");
    UMaterialInstanceConstant* OutputMaterial = nullptr;
    UMaterial* BaseMaterial = LoadObject<UMaterial>(nullptr, *BaseMaterialPath);

    // Load necessary modules
    FAssetToolsModule& AssetToolsModule =
        FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");

    if (BaseMaterial)
    {
        UMaterialInstanceConstantFactoryNew* Factory =
            NewObject<UMaterialInstanceConstantFactoryNew>();
        Factory->InitialParent = BaseMaterial;

        OutputMaterial = CastChecked<UMaterialInstanceConstant>(
            AssetToolsModule.Get().CreateAsset(ColourName,
                FPackageName::GetLongPackagePath(OutputPath),
                UMaterialInstanceConstant::StaticClass(),
                Factory));

        OutputMaterial->SetVectorParameterValueEditorOnly(FName("Colour"), ColourToCreate);
    }
    return::FReply::Handled();
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE