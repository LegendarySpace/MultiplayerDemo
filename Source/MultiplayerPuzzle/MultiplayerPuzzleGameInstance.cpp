// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerPuzzleGameInstance.h"

#include "UObject/ConstructorHelpers.h"

#include "MenuSystem/MainMenu.h"

UMultiplayerPuzzleGameInstance::UMultiplayerPuzzleGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("Constructor called"));
	ConstructorHelpers::FClassFinder<UMainMenu> MainMenuBPClass(TEXT("/Game/MultiplayerPuzzle/UI/MainMenu"));
	if (!ensure(MainMenuBPClass.Class != nullptr)) return;

	MenuClass = MainMenuBPClass.Class;
}

void UMultiplayerPuzzleGameInstance::Init()
{
	Super::Init();

	if (ensure(MenuClass != nullptr))
	{
		UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *(MenuClass->GetName()));
		return;
	}
}

void UMultiplayerPuzzleGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;

	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(Menu != nullptr)) return;

	Menu->Setup();
	Menu->SetMenuInterface(this);
}

void UMultiplayerPuzzleGameInstance::Host()
{
	if (Menu != nullptr) Menu->Teardown();

	if (!ensure(GEngine != nullptr)) return;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Hosting game"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/MultiplayerPuzzle/Maps/FirstLevel?listen");
}

void UMultiplayerPuzzleGameInstance::Join(const FString& IpAddress)
{
	if (Menu != nullptr) Menu->Teardown();

	if (!ensure(GEngine != nullptr)) return;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::Printf(TEXT("Joining game at %s"), *IpAddress));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ClientTravel(IpAddress, ETravelType::TRAVEL_Absolute, true);
}
