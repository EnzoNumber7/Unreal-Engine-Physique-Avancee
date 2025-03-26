// Copyright Epic Games, Inc. All Rights Reserved.

#include "ExoPhysiqueGameMode.h"
#include "ExoPhysiqueCharacter.h"
#include "UObject/ConstructorHelpers.h"

AExoPhysiqueGameMode::AExoPhysiqueGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
