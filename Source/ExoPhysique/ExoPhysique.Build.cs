// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ExoPhysique : ModuleRules
{
	public ExoPhysique(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Slate", "SlateCore", "FieldSystemEngine","UMG", "Niagara" });
	}
}
