// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERPUZZLE_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

protected:
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

public:
	void AddActiveTrigger();
	void RemoveActiveTrigger();

public:
	UPROPERTY(EditAnywhere)
	float MovementSpeed = 20.0;

	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true))
	FVector TargetLocation;

private:
	FVector StartLocation;
	FVector EndLocation;

	UPROPERTY(EditAnywhere)
	int32 PlatformActivations = 1;
};
