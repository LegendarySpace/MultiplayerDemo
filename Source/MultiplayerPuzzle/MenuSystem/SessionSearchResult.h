// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//#include "Styling/SlateWidgetStyleAsset.h"

#include "MainMenu.h"

#include "SessionSearchResult.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERPUZZLE_API USessionSearchResult : public UUserWidget
{
	GENERATED_BODY()

public:
	//UFUNCTION(BlueprintCallable)
	void SetServerData(FServerData Data);

	void Setup(class UMainMenu* Parent, uint32 Index);

	UFUNCTION()
	void Clicked();

	UFUNCTION(BlueprintCallable)
	void UpdateSelection(/*class USlateWidgetStyleAsset* Style*/);

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* RowButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Host;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerCount;

	UPROPERTY()
	class UMainMenu* ParentWidget;
	int32 WidgetIndex;

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bIsSelected;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bPrevious;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bIsHeader;
};
