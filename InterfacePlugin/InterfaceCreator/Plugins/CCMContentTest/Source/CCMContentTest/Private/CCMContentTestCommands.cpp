// Copyright Epic Games, Inc. All Rights Reserved.

#include "CCMContentTestCommands.h"

#define LOCTEXT_NAMESPACE "FCCMContentTestModule"

void FCCMContentTestCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "CCMContentTest", "Bring up CCMContentTest window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
