// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "BaseMenu.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERPUZZLE_API UPauseMenu : public UBaseMenu
{
	GENERATED_BODY()

protected:
	bool Initialize() override;

	UFUNCTION()
	void ExitToMainMenu();

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitButton;

	
};
