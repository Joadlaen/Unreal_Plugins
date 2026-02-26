// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "CCMStyle.h"

class FCCMCommands : public TCommands<FCCMCommands>
{
public:

	FCCMCommands()
		: TCommands<FCCMCommands>(TEXT("CCM"), NSLOCTEXT("Contexts", "CCM", "CCM Plugin"), NAME_None, FCCMStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};