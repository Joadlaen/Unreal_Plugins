// Copyright Epic Games, Inc. All Rights Reserved.

#include "CCMContent.h"
#include "CCMContentStyle.h"
#include "CCMContentCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName CCMContentTabName("CCMContent");

#define LOCTEXT_NAMESPACE "FCCMContentModule"

void FCCMContentModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FCCMContentStyle::Initialize();
	FCCMContentStyle::ReloadTextures();

	FCCMContentCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FCCMContentCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FCCMContentModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCCMContentModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(CCMContentTabName, FOnSpawnTab::CreateRaw(this, &FCCMContentModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FCCMContentTabTitle", "CCMContent"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FCCMContentModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FCCMContentStyle::Shutdown();

	FCCMContentCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CCMContentTabName);
}

TSharedRef<SDockTab> FCCMContentModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FCCMContentModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("CCMContent.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FCCMContentModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(CCMContentTabName);
}

void FCCMContentModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FCCMContentCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FCCMContentCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCCMContentModule, CCMContent)