// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

#include "Components/Button.h"


bool UMenuWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	HostButton->OnClicked.AddDynamic(this, &UMenuWidget::OnHostButtonClicked);
	JoinButton->OnClicked.AddDynamic(this, &UMenuWidget::OnJoinButtonClicked);

	return true;
}

void UMenuWidget::OnHostButtonClicked()
{

}

void UMenuWidget::OnJoinButtonClicked()
{

}

