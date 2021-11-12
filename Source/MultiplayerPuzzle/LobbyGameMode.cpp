// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameMapsSettings.h"



void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	// Count players and server travel after limit reached
	++PlayerCount;
	if (PlayerCount >= 2)
	{
		UWorld* World = GetWorld();
		if (!ensure(World != nullptr)) return;

		// Ensure Menu teardown before server travel or game only interface will not be set
		bUseSeamlessTravel = true;
		if (HasAuthority()) World->ServerTravel("/Game/MultiplayerPuzzle/Maps/FirstLevel");
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	// Remove players from count
	--PlayerCount;
}

