// Copyright Epic Games, Inc. All Rights Reserved.

#include "CCMCommands.h"

#define LOCTEXT_NAMESPACE "FCCMModule"

void FCCMCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "CCM", "Bring up CCM window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
