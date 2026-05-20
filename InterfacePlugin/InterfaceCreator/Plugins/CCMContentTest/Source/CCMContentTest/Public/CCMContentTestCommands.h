// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"
#include "CCMContentTestStyle.h"

class FCCMContentTestCommands : public TCommands<FCCMContentTestCommands>
{
public:

	FCCMContentTestCommands()
		: TCommands<FCCMContentTestCommands>(TEXT("CCMContentTest"), NSLOCTEXT("Contexts", "CCMContentTest", "CCMContentTest Plugin"), NAME_None, FCCMContentTestStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};