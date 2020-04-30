// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	DoorRequirement = EDoorRequirement::EDR_FloorSwitches;

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
		UE_LOG(LogTemp, Warning, TEXT("Door has Actor Destruction Requirement"));
		break;
	case EDoorRequirement::EDR_FloorSwitches:
		UE_LOG(LogTemp, Warning, TEXT("Door has Floor Switch Requirement"));
		break;
	case EDoorRequirement::EDR_Position:
		UE_LOG(LogTemp, Warning, TEXT("Door has Position Requirement"));
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Door has no Requirement"));
	}
}

void ADoor::UpdateDoorPosition(float Z)
{
	FVector NewPosition = InitialDoorPosition;
	NewPosition.Z += Z;
	StaticMesh->SetWorldLocation(NewPosition);
}