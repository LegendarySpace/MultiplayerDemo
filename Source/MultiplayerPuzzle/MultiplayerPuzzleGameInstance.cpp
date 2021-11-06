// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerPuzzleGameInstance.h"

UMultiplayerPuzzleGameInstance::UMultiplayerPuzzleGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("Constructor called"));
}

void UMultiplayerPuzzleGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("Initializer called"));
}

void UMultiplayerPuzzleGameInstance::Host()
{
	if (!ensure(GEngine != nullptr)) return;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Hosting game"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	World->ServerTravel("/Game/MultiplayerPuzzle/Maps/FirstLevel?listen");
}

void UMultiplayerPuzzleGameInstance::Join(const FString& IpAddress)
{
	if (!ensure(GEngine != nullptr)) return;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::Printf(TEXT("Joining game at %s"), *IpAddress));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ClientTravel(IpAddress, ETravelType::TRAVEL_Absolute, true);
}
