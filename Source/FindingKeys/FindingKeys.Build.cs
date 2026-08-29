// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FindingKeys : ModuleRules
{
	public FindingKeys(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[] { 
				"Core", 
				"CoreUObject", 
				"Engine", 
				"InputCore", 
				"EnhancedInput", 
				"OnlineSubsystem", 
				"OnlineSubsystemUtils",
			});

		DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
	}
}
