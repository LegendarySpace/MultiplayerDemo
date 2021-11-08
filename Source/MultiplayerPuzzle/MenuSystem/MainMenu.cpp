// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"


bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	HostButton->OnClicked.AddDynamic(this, &UMainMenu::OpenHostMenu);
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	HostCancelButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	HostAcceptButton->OnClicked.AddDynamic(this, &UMainMenu::AttemptHost);
	JoinCancelButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	JoinAcceptButton->OnClicked.AddDynamic(this, &UMainMenu::AttemptJoin);

	return true;
}

void UMainMenu::CloseMenu_Implementation()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand(TEXT("quit"));
}

void UMainMenu::OpenMainMenu()
{

	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::OpenHostMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(HostMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(HostMenu);
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::AttemptHost()
{
	if (!ensure(MenuInterface != nullptr)) return;
	MenuInterface->Host();
}

void UMainMenu::AttemptJoin()
{
	if (!ensure(MenuInterface != nullptr)) return;
	FString Address = AddressInput->GetText().ToString();
	MenuInterface->Join(Address);
}

