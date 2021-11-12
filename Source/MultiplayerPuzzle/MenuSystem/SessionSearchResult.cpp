// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionSearchResult.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
//#include "Styling/SlateWidgetStyleAsset.h"




void USessionSearchResult::SetServerData(FServerData Data)
{
	ServerName->SetText(FText::FromString(Data.Name));
	Host->SetText(FText::FromString(Data.HostUsername));
	PlayerCount->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), Data.CurrentPlayers, Data.MaxPlayers)));
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

void USessionSearchResult::UpdateSelection(/*USlateWidgetStyleAsset* Style*/)
{
	if (bIsSelected != bPrevious)
	{
		//SButton::FArguments ButtonDefaults;
		//ButtonDefaults.ButtonStyle(Style);
		//RowButton->WidgetStyle = *ButtonDefaults._ButtonStyle;
		bPrevious = bIsSelected;
	}
}

