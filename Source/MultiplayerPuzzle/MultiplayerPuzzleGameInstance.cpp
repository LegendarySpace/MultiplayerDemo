// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerPuzzleGameInstance.h"

#include "UObject/ConstructorHelpers.h"

#include "MenuSystem/MainMenuWidget.h"

UMultiplayerPuzzleGameInstance::UMultiplayerPuzzleGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("Constructor called"));
	ConstructorHelpers::FClassFinder<UMainMenuWidget> MainMenuWidgetBPClass(TEXT("/Game/MultiplayerPuzzle/UI/MainMenu"));
	if (!ensure(MainMenuWidgetBPClass.Class != nullptr)) return;

	MenuClass = MainMenuWidgetBPClass.Class;
}

void UMultiplayerPuzzleGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
}

void UMultiplayerPuzzleGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;

	Menu = CreateWidget<UMainMenuWidget>(this, MenuClass);
	if (!ensure(Menu != nullptr)) return;

	Menu->Setup();
	Menu->SetMenuInterface(this);
}

void UMultiplayerPuzzleGameInstance::Host()
{
	if (Menu != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Teardown menu"));
		Menu->Teardown();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Menu not valid"));
	}

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
