// Copyright Epic Games, Inc. All Rights Reserved.

#include "CCMContentTest.h"
#include "CCMContentTestStyle.h"
#include "CCMContentTestCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "SCCMWidget.h"

static const FName CCMContentTestTabName("CCMContentTest");

#define LOCTEXT_NAMESPACE "FCCMContentTestModule"

void FCCMContentTestModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FCCMContentTestStyle::Initialize();
	FCCMContentTestStyle::ReloadTextures();

	FCCMContentTestCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FCCMContentTestCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FCCMContentTestModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCCMContentTestModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(CCMContentTestTabName, FOnSpawnTab::CreateRaw(this, &FCCMContentTestModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FCCMContentTestTabTitle", "CCMContentTest"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FCCMContentTestModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FCCMContentTestStyle::Shutdown();

	FCCMContentTestCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CCMContentTestTabName);
}

TSharedRef<SDockTab> FCCMContentTestModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FString ImagePath = FPaths::ProjectContentDir() / TEXT("/Plugins/CCMContentTest/Content/White.png");
	FName BrushName = FName(*ImagePath);

	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FCCMContentTestModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("CCMContentTest.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.Padding(10, 10)
				.MaxHeight(30)
				[
					SNew(SHorizontalBox)
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
								.Text(FText::FromString(""))
								.HintText(LOCTEXT("CM_ColourName_Label", "Please provide a unique Colour name"))
						]
				]
			+SVerticalBox::Slot()
				.Padding(10, 10)
				[
					SNew(SCCMWidget)
				]
		];
}

void FCCMContentTestModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(CCMContentTestTabName);
}

void FCCMContentTestModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FCCMContentTestCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FCCMContentTestCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCCMContentTestModule, CCMContentTest)