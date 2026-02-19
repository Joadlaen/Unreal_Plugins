// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class limp_bizkit : ModuleRules
{
	public limp_bizkit(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"limp_bizkit",
			"limp_bizkit/Variant_Horror",
			"limp_bizkit/Variant_Horror/UI",
			"limp_bizkit/Variant_Shooter",
			"limp_bizkit/Variant_Shooter/AI",
			"limp_bizkit/Variant_Shooter/UI",
			"limp_bizkit/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
