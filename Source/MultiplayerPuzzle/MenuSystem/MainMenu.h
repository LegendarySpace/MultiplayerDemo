// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "BaseMenu.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERPUZZLE_API UMainMenu : public UBaseMenu
{
	GENERATED_BODY()

public:
	UMainMenu(const FObjectInitializer& ObjectInitializer);

protected:
	bool Initialize() override;

public:
	void CloseMenu_Implementation() override;

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

	UFUNCTION()
	void SetServerList(TArray<FString> ServerNames);

	void SelectIndex(uint32 Index);

private:
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
	class UScrollBox* SearchScrollBox;

	UPROPERTY(meta = (BindWidget))
	class UButton* HostCancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* HostAcceptButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinCancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinAcceptButton;

	UPROPERTY(meta = (BindWidget))
	class USessionSearchResult* Header;

	TSubclassOf<class UUserWidget> SearchResultClass;

	TOptional<uint32> SelectedIndex;
};
