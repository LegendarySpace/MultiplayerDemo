// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMenu.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"


bool UBaseMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(CloseButton != nullptr)) return false;
	CloseButton->OnClicked.AddDynamic(this, &UBaseMenu::CloseMenu);

	return true;
}

void UBaseMenu::Setup()
{
	this->AddToViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
}

void UBaseMenu::Teardown()
{
	this->RemoveFromViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeGameOnly InputModeData;
	InputModeData.SetConsumeCaptureMouseDown(true);

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;
}

void UBaseMenu::CloseMenu()
{
	CloseMenu_Implementation();
}

void UBaseMenu::CloseMenu_Implementation()
{
	Teardown();
}

void UBaseMenu::SetMenuInterface(IMenuInterface* Interface)
{
	MenuInterface = Interface;
}

