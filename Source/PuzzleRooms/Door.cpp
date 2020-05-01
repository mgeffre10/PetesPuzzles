// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "FloorSwitch.h"
#include "InteractableObject.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());

	DoorRequirement = EDoorRequirement::EDR_FloorSwitches;

	bIsDoorOpen = false;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	InitialDoorPosition = StaticMesh->GetComponentLocation();
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckDoorRequirements();
}

void ADoor::CheckDoorRequirements()
{
	switch (DoorRequirement)
	{
	case EDoorRequirement::EDR_ActorDestruction:
		if (!bIsDoorOpen)
		{
			if (ActorsToBeDestroyed.Num() > 0)
			{
				if (AreActorsDestroyed())
				{
					bIsDoorOpen = true;
					OpenDoor();
				}
			}
		}
		break;
	case EDoorRequirement::EDR_FloorSwitches:
		if (FloorSwitches.Num() > 0)
		{
			if (AreButtonsPressed())
			{
				bIsDoorOpen = true;
				OpenDoor();
			}
			else
			{
				CloseDoor();
			}
		}
		break;
	case EDoorRequirement::EDR_Position:
		if (!bIsDoorOpen)
		{
			const FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation();

			if (PlayerLocation.X > 900.f)
			{
				bIsDoorOpen = true;
				OpenDoor();
			}
		}
		break;
	case EDoorRequirement::EDR_None:
		if (!bIsDoorOpen)
		{
			bIsDoorOpen = true;
			OpenDoor();
		}
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Unknown Requirement"));
	}
}

void ADoor::UpdateDoorPosition(float Y)
{
	FVector NewPosition = InitialDoorPosition;
	NewPosition.Y += Y;
	StaticMesh->SetWorldLocation(NewPosition);
}

bool ADoor::AreButtonsPressed()
{
	bool bButtonsPressed = true;

	for (AFloorSwitch* FloorSwitch : FloorSwitches)
	{
		if (!FloorSwitch->IsButtonPressed())
		{
			bButtonsPressed = false;
		}
	}

	return bButtonsPressed;
}

bool ADoor::AreActorsDestroyed()
{
	bool bActorsDestroyed = true;

	for (AInteractableObject* InteractableObj : ActorsToBeDestroyed)
	{
		if (!InteractableObj->bIsDestroyed)
		{
			bActorsDestroyed = false;
		}
	}

	return bActorsDestroyed;
}