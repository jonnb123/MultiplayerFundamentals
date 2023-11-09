// Copyright Epic Games, Inc. All Rights Reserved.

#include "MultiplayerCourseGameMode.h"
#include "MultiplayerCourseCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMultiplayerCourseGameMode::AMultiplayerCourseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

// for server travel
void AMultiplayerCourseGameMode::HostLANGame()
{
	// loads the map ?Listen makes the game launch as a listen server
	GetWorld()->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?Listen");
}

// for client travel 
void AMultiplayerCourseGameMode::JoinLANGame()
{
	// we only get the first local player controller because we only have a single local player on a client machine
	APlayerController* PC = GetGameInstance()->GetFirstLocalPlayerController();
	if (PC)
	{
		// go to cmd prompt, use cmd ipconfig to get ip address: 192.168.1.13
		PC->ClientTravel("192.168.1.13", TRAVEL_Absolute);
	}
}
