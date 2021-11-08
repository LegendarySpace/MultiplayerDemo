// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

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
	void Join(const FString& IpAddress) override;

	UFUNCTION(BlueprintCallable)
	void LoadMainMenu() override;

	UFUNCTION(BlueprintCallable)
	void LoadPauseMenu() override;

	void ReturnToMainMenu() override;

private:
	TSubclassOf<class UMainMenu> MainMenuClass;

	TSubclassOf<class UPauseMenu> PauseMenuClass;

	class UBaseMenu* Menu;
};
