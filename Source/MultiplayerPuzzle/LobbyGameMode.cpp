// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameMapsSettings.h"

#include "MultiplayerPuzzleGameInstance.h"


void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	// Count players and server travel after limit reached
	++PlayerCount;
	if (PlayerCount >= 2)
	{
		GetWorldTimerManager().SetTimer(GameLaunchHandle, this, &ALobbyGameMode::LaunchGame, 5.f);
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	// Remove players from count
	--PlayerCount;
}

void ALobbyGameMode::LaunchGame()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	auto Instance = Cast<UMultiplayerPuzzleGameInstance>(GetGameInstance());
	Instance->StartSession();

	// Ensure Menu teardown before server travel or game only interface will not be set
	bUseSeamlessTravel = true;
	if (HasAuthority()) World->ServerTravel("/Game/MultiplayerPuzzle/Maps/FirstLevel");
}

