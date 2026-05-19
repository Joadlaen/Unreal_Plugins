// Copyright Epic Games, Inc. All Rights Reserved.

#include "CCMContentCommands.h"

#define LOCTEXT_NAMESPACE "FCCMContentModule"

void FCCMContentCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "CCMContent", "Bring up CCMContent window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
