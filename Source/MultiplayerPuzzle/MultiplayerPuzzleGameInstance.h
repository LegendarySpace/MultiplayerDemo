// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

#include "MenuSystem/MenuInterface.h"

#include "MultiplayerPuzzleGameInstance.generated.h"

/**
 *
 */
UCLASS()
class MULTIPLAYERPUZZLE_API UMultiplayerPuzzleGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UMultiplayerPuzzleGameInstance(const FObjectInitializer& ObjectInitializer);

	void Init() override;

	UFUNCTION(Exec)
	void Host() override;

	UFUNCTION(Exec)
	void Join(const uint32 Index) override;

	UFUNCTION(BlueprintCallable)
	void LoadMainMenu() override;

	UFUNCTION(BlueprintCallable)
	void LoadPauseMenu() override;

	void ReturnToMainMenu() override;

	void SearchForSessions() override;

private:
	void CreateSession();
	void SessionCreated(FName Name, bool Success);
	void SessionDestroyed(FName Name, bool Success);
	void SessionsFound(bool Success);
	void SessionJoined(FName Name, EOnJoinSessionCompleteResult::Type ResultType);

public:
	FName ServerName;

private:
	TSubclassOf<class UMainMenu> MainMenuClass;

	TSubclassOf<class UPauseMenu> PauseMenuClass;

	class UMainMenu* Menu;

	class IOnlineSubsystem* OnlineSubsystem;

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
};
