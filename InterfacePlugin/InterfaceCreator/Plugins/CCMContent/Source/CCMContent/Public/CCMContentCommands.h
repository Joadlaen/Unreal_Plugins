// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"
#include "CCMContentStyle.h"

class FCCMContentCommands : public TCommands<FCCMContentCommands>
{
public:

	FCCMContentCommands()
		: TCommands<FCCMContentCommands>(TEXT("CCMContent"), NSLOCTEXT("Contexts", "CCMContent", "CCMContent Plugin"), NAME_None, FCCMContentStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};