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

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& IpAddress);

private:
	TSubclassOf<class UMainMenu> MenuClass;

	class UMainMenu* Menu;
};
