// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "ProjectileSystem.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());

	MovementType = EPlatformMovementType::EPMT_Static;

	// Setting ProjectileSystem and PathVectors References in Editor

	bPlatformIsMoving = false;
	bIsIteratingForward = true;
	bPlatformHasTimer = false;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// Insert Platform Position at beginning of Vector
	PathVectors.Insert(GetActorLocation(), 0);

	if (PlatformHasPath())
	{
		CurrentStartVectorIndex = 0;
		CurrentDestinationVectorIndex = 1;
	}

	if (bPlatformHasTimer)
	{
		RemainingPauseTime = PlatformPauseTime;
	}

	switch (MovementType)
	{
		// Don't need EPMT_Static because it doesn't do anything
		case EPlatformMovementType::EPMT_Projectile:
			break;
		case EPlatformMovementType::EPMT_Constant:
			StartMovementLerp();
			break;
		default:
			break;
	}
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bPlatformIsMoving)
	{
		if (MovementType == EPlatformMovementType::EPMT_Projectile)
		{
			if (ProjectileSystem && ProjectileSystem->HasSystemCompleted())
			{
				bPlatformIsMoving = true;
				StartMovementLerp();
			}
		}
	}
}

void AMovingPlatform::MovePlatform(float Alpha)
{
	SetActorLocation(FMath::Lerp(PathVectors[CurrentStartVectorIndex], PathVectors[CurrentDestinationVectorIndex], Alpha));
}

void AMovingPlatform::UpdateCurrentVectors()
{
	if (bIsIteratingForward)
	{
		CurrentStartVectorIndex++;

		if (CurrentDestinationVectorIndex != PathVectors.Num() - 1)
		{
			CurrentDestinationVectorIndex++;
			StartMovementLerp();
		}
		else
		{
				CurrentDestinationVectorIndex = CurrentStartVectorIndex - 1;

				// Platform should now decrement through PathVector index
				bIsIteratingForward = false;

				// Set Timer if bPlatformHasTimer
				StartMovementLerp();
		}
	}
	else
	{
		CurrentStartVectorIndex--;

		if (CurrentDestinationVectorIndex != 0)
		{
			CurrentDestinationVectorIndex--;
			StartMovementLerp();
		}
		else
		{
				CurrentDestinationVectorIndex = CurrentStartVectorIndex + 1;

				// Platform should now increment through PathVector index
				bIsIteratingForward = true;
				// Set Timer if bPlatformHasTimer

				StartMovementLerp();
		}
	}
}