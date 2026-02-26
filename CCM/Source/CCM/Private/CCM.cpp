// Copyright Epic Games, Inc. All Rights Reserved.

#include "CCM.h"
#include "CCMStyle.h"
#include "CCMCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "Engine/RendererSettings.h"
#include "Widgets/Layout/SUniformGridPanel.h"
#include "Widgets/Layout/SWrapBox.h"

static const FName CCMTabName("CCM");

#define LOCTEXT_NAMESPACE "FCCMModule"

void FCCMModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FCCMStyle::Initialize();
	FCCMStyle::ReloadTextures();

	FCCMCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FCCMCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FCCMModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCCMModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(CCMTabName, FOnSpawnTab::CreateRaw(this, &FCCMModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FCCMTabTitle", "CCM"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FCCMModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FCCMStyle::Shutdown();

	FCCMCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CCMTabName);
}

TSharedRef<SDockTab> FCCMModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FString ImagePath = FPaths::ProjectContentDir() / TEXT("/Plugins/CCM/Content/Images/White.png");
	FName BrushName = FName(*ImagePath);
	
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FCCMModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("CCM.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.Padding(10,10)
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.Padding(10,10)
				[
					SNew(SBorder)
						.BorderBackgroundColor(FColor(50,50,255,255))
						.BorderImage(new FSlateImageBrush(BrushName,FVector2D(2,2)))
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
				]
				+SHorizontalBox::Slot()
				.Padding(10,10)
				[
					SNew(SBorder)
						.BorderBackgroundColor(FColor(50,255,50,255))
						.BorderImage(new FSlateImageBrush(BrushName,FVector2D(2,2)))
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
				]
			]
			+SVerticalBox::Slot()
			.Padding(20,10) 
			[
				SNew(SBorder)
					.BorderBackgroundColor(FColor(255,50,50,255))
					.BorderImage(new FSlateImageBrush(BrushName,FVector2D(2,2)))
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
			]
		];
}

void FCCMModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(CCMTabName);
}

void FCCMModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FCCMCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FCCMCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCCMModule, CCM)