// Copyright Epic Games, Inc. All Rights Reserved.

#include "MySnapButton.h"

#include "Selection.h"
#include "Modules/ModuleManager.h"
#include "ToolMenus.h"
#include "Subsystems/EditorActorSubsystem.h"

#define LOCTEXT_NAMESPACE "FMySnapButtonModule"

void FMySnapButtonModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(
			this, &FMySnapButtonModule::RegisterMenuExtensions));
}

void FMySnapButtonModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
}

void FMySnapButtonModule::RegisterMenuExtensions()
{
	// Use the current object as the owner of the menus
	// This allows us to remove all our custom menus when the 
	// module is unloaded (see ShutdownModule below)
	FToolMenuOwnerScoped OwnerScoped(this);

	// Extend the "File" section of the main toolbar
	UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu(
		"LevelEditor.LevelEditorToolBar.ModesToolBar");
	
	FToolMenuSection& ToolbarSection = ToolbarMenu->FindOrAddSection("HelloWorld");
 
	ToolbarSection.AddEntry(FToolMenuEntry::InitToolBarButton(
		TEXT("Proof Of Life!"),
		FExecuteAction::CreateRaw(this,&FMySnapButtonModule::ButtonFunctionality),
		INVTEXT("This is the button label"),
		INVTEXT("This is the button tooltip"),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Comment")
	));
}

void FMySnapButtonModule::ButtonFunctionality()
{
	USelection* SelectedActors = GEditor->GetSelectedActors();
	for (FSelectionIterator Iter(*SelectedActors); Iter; ++Iter)
	{
		AActor* Actor = Cast<AActor>(*Iter);
		if (Actor)
		{
			UE_LOG(LogTemp, Display, TEXT("The Grid Size is %f"), GEditor->GetGridSize());
			FVector ModActorLocation = Actor->GetActorLocation();
			ModActorLocation.X = FMath::GridSnap(Actor->GetActorLocation().X,GEditor->GetGridSize());
			ModActorLocation.Y = FMath::GridSnap(Actor->GetActorLocation().Y,GEditor->GetGridSize());
			ModActorLocation.Z = FMath::GridSnap(Actor->GetActorLocation().Z,GEditor->GetGridSize());

			Actor->SetActorLocation(ModActorLocation,false,nullptr);
			UE_LOG(LogTemp, Display, TEXT("Actor snapped to %s"), *ModActorLocation.ToString());
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMySnapButtonModule, MySnapButton)