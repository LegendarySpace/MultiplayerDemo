// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Styling/SlateWidgetStyleAsset.h"

#include "SessionSearchResult.h"


UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> SessionSearchResultBPClass(TEXT("/Game/MultiplayerPuzzle/UI/WBP_SessionRow"));
	if (!ensure(SessionSearchResultBPClass.Class != nullptr)) return;

	SearchResultClass = SessionSearchResultBPClass.Class;

	//ConstructorHelpers::FObjectFinder<USlateWidgetStyleAsset> UnselectedStyleBP(TEXT("/Game/MultiplayerPuzzle/UI/SquareButtonUnselected"));
	//ConstructorHelpers::FObjectFinder<USlateWidgetStyleAsset> SelectedStyleBP(TEXT("/Game/MultiplayerPuzzle/UI/SquareButtonUnselected"));
	//if (!ensure(UnselectedStyleBP.Object != nullptr) && !ensure(SelectedStyleBP.Object != nullptr)) return;

	//UnselectedStyle = UnselectedStyleBP.Object;
	//SelectedStyle = SelectedStyleBP.Object;
}

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
	if (!ensure(MenuSwitcher != nullptr) ||
		!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);

	if (MenuInterface == nullptr) return;
	MenuInterface->SearchForSessions();
}

void UMainMenu::AttemptHost()
{
	if (!ensure(MenuInterface != nullptr)) return;
	MenuInterface->SetDesiredServerName(HostNameInput->GetText().ToString());
	MenuInterface->Host();
}

void UMainMenu::AttemptJoin()
{
	if (!ensure(MenuInterface != nullptr) ||
		!ensure(SearchScrollBox != nullptr)) return;

	if (SelectedIndex.IsSet())
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Index: %d"), SelectedIndex.GetValue());
		MenuInterface->Join(SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Index not set"));
	}
}

void UMainMenu::SetServerList(TArray<FServerData> ServerDataList)
{
	if (!ensure(SearchScrollBox != nullptr)) return;
	SearchScrollBox->ClearChildren();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	uint32 i = 0;
	for (const FServerData& ServerData : ServerDataList)
	{
		auto Row = CreateWidget<USessionSearchResult>(World, SearchResultClass);
		if (!ensure(Row != nullptr)) return;
		FString str = FString::Printf(TEXT("%d / %d"), ServerData.CurrentPlayers, ServerData.MaxPlayers);
		Row->SetServerData(ServerData);
		Row->Setup(this, i);
		++i;
		
		SearchScrollBox->AddChild(Row);
	}
}

void UMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
	UpdateChildren();
}

void UMainMenu::UpdateChildren()
{
	if (!ensure(SearchScrollBox != nullptr)) return;

	for (int32 i = 0; i < SearchScrollBox->GetChildrenCount(); i++)
	{
		auto Row = Cast<USessionSearchResult>(SearchScrollBox->GetChildAt(i));
		if (Row != nullptr)
		{
			bool sel = SelectedIndex.IsSet() && SelectedIndex.GetValue() == i;
			Row->bIsSelected = sel;
			//if (sel) Row->UpdateSelection(SelectedStyle);
			//else Row->UpdateSelection(UnselectedStyle);
		}
	}
}

