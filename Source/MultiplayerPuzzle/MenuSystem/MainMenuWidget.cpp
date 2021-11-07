// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

#include "Components/Button.h"


bool UMainMenuWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	HostButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnHostButtonClicked);
	JoinButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnJoinButtonClicked);

	return true;
}

void UMainMenuWidget::Setup()
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

void UMainMenuWidget::Teardown()
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

void UMainMenuWidget::SetMenuInterface(IMenuInterface* Interface)
{
	MenuInterface = Interface;
}

void UMainMenuWidget::OnHostButtonClicked()
{
	if (!ensure(GEngine != nullptr)) return;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, TEXT("Host Clicked"));

	if (!ensure(MenuInterface != nullptr)) return;
	MenuInterface->Host();
}

void UMainMenuWidget::OnJoinButtonClicked()
{
	if (!ensure(GEngine != nullptr)) return;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Magenta, TEXT("Join Clicked"));
}

