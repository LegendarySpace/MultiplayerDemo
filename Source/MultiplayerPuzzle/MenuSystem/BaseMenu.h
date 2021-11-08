// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MenuInterface.h"
#include "BaseMenu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERPUZZLE_API UBaseMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	bool Initialize() override;

public:
	UFUNCTION(BlueprintCallable)
	void Setup();

	void Teardown();

	UFUNCTION(BlueprintCallable)
	void CloseMenu();
	virtual void CloseMenu_Implementation();

	void SetMenuInterface(IMenuInterface* Interface);

protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* Background;

	UPROPERTY(meta = (BindWidget))
	class UImage* MenuBackground;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UButton* CloseButton;

	IMenuInterface* MenuInterface;
};
