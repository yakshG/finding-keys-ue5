// Copyright Epic Games, Inc. All Rights Reserved.

#include "MultiplayerCoOpGameMode.h"
#include "MultiplayerCoOpCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMultiplayerCoOpGameMode::AMultiplayerCoOpGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
