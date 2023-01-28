// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Cube_Collecting : ModuleRules
{
	public Cube_Collecting(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
