// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SessionSearchResult.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERPUZZLE_API USessionSearchResult : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetServerData(const FString& Name, const FString& HostPlayer, const FString& Count);

	void Setup(class UMainMenu* Parent, uint32 Index);

	UFUNCTION()
	void Clicked();

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
};
