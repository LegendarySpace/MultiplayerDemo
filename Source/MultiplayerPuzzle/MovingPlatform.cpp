// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
	StartLocation = GetActorLocation();
	EndLocation = TargetLocation + StartLocation;
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (HasAuthority() && PlatformActivations >= 1)
	{
		// If current distance from Start is > End distance from Start swap them
		if (FVector::Distance(GetActorLocation(), StartLocation) > FVector::Distance(EndLocation, StartLocation))
		{
			FVector temp = StartLocation;
			StartLocation = EndLocation;
			EndLocation = temp;
		}
		FVector Location = GetActorLocation();
		FVector Direction = (EndLocation - StartLocation).GetSafeNormal();
		Location += MovementSpeed * DeltaTime * Direction;
		SetActorLocation(Location);
	}
}

void AMovingPlatform::AddActiveTrigger()
{
	PlatformActivations++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	PlatformActivations--;
}
