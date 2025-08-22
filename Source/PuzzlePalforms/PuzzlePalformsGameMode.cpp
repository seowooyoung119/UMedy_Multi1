// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuzzlePalformsGameMode.h"
#include "PuzzlePalformsCharacter.h"
#include "UObject/ConstructorHelpers.h"

APuzzlePalformsGameMode::APuzzlePalformsGameMode()
{
	UE_LOG(LogTemp, Warning, TEXT("APuzzlePalformsGameMode Constructor"));
	
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
