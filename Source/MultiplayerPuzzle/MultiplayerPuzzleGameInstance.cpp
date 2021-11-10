// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerPuzzleGameInstance.h"

#include "UObject/ConstructorHelpers.h"
#include "OnlineSubsystem.h"


#include "MenuSystem/MainMenu.h"
#include "MenuSystem/PauseMenu.h"

const FName SESSION_NAME = TEXT("MPGameSession");

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

	OnlineSubsystem = IOnlineSubsystem::Get(TEXT("NULL"));

	if (OnlineSubsystem != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Online Subsystem: %s"), *OnlineSubsystem->GetSubsystemName().ToString());
		SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMultiplayerPuzzleGameInstance::SessionCreated);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UMultiplayerPuzzleGameInstance::SessionDestroyed);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UMultiplayerPuzzleGameInstance::SessionsFound);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find Online Subsystem"));
	}
}

void UMultiplayerPuzzleGameInstance::Host()
{
	if (SessionInterface.IsValid())
	{
		auto Sesh = SessionInterface->GetNamedSession(SESSION_NAME);
		if (Sesh != nullptr)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			CreateSession();
		}

	}
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

void UMultiplayerPuzzleGameInstance::SearchForSessions()
{
	if (SessionInterface.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Starting Search for Sessions"));
		SessionSearch = MakeShareable(new FOnlineSessionSearch());
		if (SessionSearch.IsValid())
		{
			SessionSearch->bIsLanQuery = true;
			//SessionSearch->QuerySettings();
			SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
		}
	}
}

void UMultiplayerPuzzleGameInstance::SessionCreated(FName Name, bool Success)
{
	if (Success)
	{
		if (Menu != nullptr) Menu->Teardown();

		if (!ensure(GEngine != nullptr)) return;
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Hosting game"));

		UWorld* World = GetWorld();
		if (!ensure(World != nullptr)) return;

		World->ServerTravel("/Game/MultiplayerPuzzle/Maps/FirstLevel?listen");
	}
}

void UMultiplayerPuzzleGameInstance::SessionDestroyed(FName Name, bool Success)
{
	if (!Success) return;
	UE_LOG(LogTemp, Warning, TEXT("Session Destroyed"));
	CreateSession();
}

void UMultiplayerPuzzleGameInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsLANMatch = true;
		SessionSettings.NumPublicConnections = 4;
		SessionSettings.bShouldAdvertise = true;

		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
	}
}

void UMultiplayerPuzzleGameInstance::SessionsFound(bool Success)
{
	if (Success && SessionSearch.IsValid() && Menu != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Finished Searching for Sessions"));

		TArray<FString> Names;
		for (auto Result : SessionSearch->SearchResults)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found Session: %s"), *Result.Session.GetSessionIdStr());
			Names.Add(Result.Session.GetSessionIdStr());
		}

		Menu->SetServerList(Names);
	}
}

