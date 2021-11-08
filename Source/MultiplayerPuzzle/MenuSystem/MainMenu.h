// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MenuInterface.h"

#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERPUZZLE_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	bool Initialize() override;

public:
	void Setup();

	void Teardown();

	void SetMenuInterface(IMenuInterface* Interface);

	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void OpenHostMenu();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void AttemptHost();

	UFUNCTION()
	void AttemptJoin();

private:
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* HostMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* HostNameInput;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* AddressInput;

	UPROPERTY(meta = (BindWidget))
	class UButton* HostCancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* HostAcceptButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinCancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinAcceptButton;

	IMenuInterface* MenuInterface;
};
