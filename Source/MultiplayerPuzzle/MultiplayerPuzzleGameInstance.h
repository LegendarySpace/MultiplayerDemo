// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MultiplayerPuzzleGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERPUZZLE_API UMultiplayerPuzzleGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMultiplayerPuzzleGameInstance(const FObjectInitializer& ObjectInitializer);

	void Init() override;

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& IpAddress);
};
