// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "codingExperience04GameMode.h"
#include "codingExperience04Character.h"
#include "UObject/ConstructorHelpers.h"

AcodingExperience04GameMode::AcodingExperience04GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
