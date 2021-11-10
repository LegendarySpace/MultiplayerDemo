// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionSearchResult.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "MainMenu.h"



void USessionSearchResult::SetServerData(const FString& Name, const FString& HostPlayer, const FString& Count)
{
	ServerName->SetText(FText::FromString(Name));
	Host->SetText(FText::FromString(HostPlayer));
	PlayerCount->SetText(FText::FromString(Count));
}

void USessionSearchResult::Setup(class UMainMenu* Parent, uint32 Index)
{
	if (!ensure(RowButton != nullptr)) return;

	RowButton->OnClicked.AddDynamic(this, &USessionSearchResult::Clicked);

	ParentWidget = Parent;
	WidgetIndex = Index;
}

void USessionSearchResult::Clicked()
{
	if (!ensure(ParentWidget != nullptr)) return;
	ParentWidget->SelectIndex(WidgetIndex);
}

