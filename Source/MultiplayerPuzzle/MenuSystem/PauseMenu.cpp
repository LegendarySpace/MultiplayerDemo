// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "Components/Button.h"


bool UPauseMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(ExitButton != nullptr)) return false;
	ExitButton->OnClicked.AddDynamic(this, &UPauseMenu::ExitToMainMenu);

	return true;
}

void UPauseMenu::ExitToMainMenu()
{
	if (!ensure(MenuInterface != nullptr)) return;

	this->Teardown();
	MenuInterface->ReturnToMainMenu();
}

