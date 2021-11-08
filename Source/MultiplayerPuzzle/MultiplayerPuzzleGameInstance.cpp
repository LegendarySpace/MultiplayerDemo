// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerPuzzleGameInstance.h"

#include "UObject/ConstructorHelpers.h"

#include "MenuSystem/MainMenu.h"
#include "MenuSystem/PauseMenu.h"

UMultiplayerPuzzleGameInstance::UMultiplayerPuzzleGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("Constructor called"));

	ConstructorHelpers::FClassFinder<UMainMenu> MainMenuBPClass(TEXT("/Game/MultiplayerPuzzle/UI/WBP_MainMenu"));
	if (!ensure(MainMenuBPClass.Class != nullptr)) return;

	ConstructorHelpers::FClassFinder<UPauseMenu> PauseMenuBPClass(TEXT("/Game/MultiplayerPuzzle/UI/WBP_PauseMenu"));
	if (!ensure(PauseMenuBPClass.Class != nullptr)) return;

	MainMenuClass = MainMenuBPClass.Class;
	PauseMenuClass = PauseMenuBPClass.Class;
}

void UMultiplayerPuzzleGameInstance::Init()
{
	Super::Init();

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

void UMultiplayerPuzzleGameInstance::LoadMainMenu()
{
	if (!ensure(MainMenuClass != nullptr)) return;

	Menu = CreateWidget<UMainMenu>(this, MainMenuClass);
	if (!ensure(Menu != nullptr)) return;

	Menu->Setup();
	Menu->SetMenuInterface(this);
}

void UMultiplayerPuzzleGameInstance::LoadPauseMenu()
{
	if (!ensure(MainMenuClass != nullptr)) return;

	auto PauseMenu = CreateWidget<UPauseMenu>(this, PauseMenuClass);
	if (!ensure(PauseMenu != nullptr)) return;

	PauseMenu->Setup();
	PauseMenu->SetMenuInterface(this);
}

void UMultiplayerPuzzleGameInstance::ReturnToMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/MultiplayerPuzzle/Maps/MainMenu", ETravelType::TRAVEL_Absolute);
}
