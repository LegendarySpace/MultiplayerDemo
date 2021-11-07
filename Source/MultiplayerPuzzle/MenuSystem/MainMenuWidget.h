// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MenuInterface.h"

#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERPUZZLE_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	bool Initialize() override;

public:
	void Setup();

	void Teardown();

	void SetMenuInterface(IMenuInterface* Interface);

	UFUNCTION()
	void OnHostButtonClicked();

	UFUNCTION()
	void OnJoinButtonClicked();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	IMenuInterface* MenuInterface;
};
