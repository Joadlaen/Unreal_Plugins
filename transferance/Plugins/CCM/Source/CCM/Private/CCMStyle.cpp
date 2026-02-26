// Copyright Epic Games, Inc. All Rights Reserved.

#include "CCMStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FCCMStyle::StyleInstance = nullptr;

void FCCMStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FCCMStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FCCMStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("CCMStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FCCMStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("CCMStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("CCM")->GetBaseDir() / TEXT("Resources"));

	Style->Set("CCM.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	return Style;
}

void FCCMStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FCCMStyle::Get()
{
	return *StyleInstance;
}
