// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorSwitch.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "TimerManager.h"

// Sets default values
AFloorSwitch::AFloorSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	RootComponent = TriggerVolume;

	/** Ensure Trigger Volume only responds to pawn for now */
	TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerVolume->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	TriggerVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Overlap);

	FloorSwitchBorder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorSwitchBorder"));
	FloorSwitchBorder->SetupAttachment(GetRootComponent());

	FloorSwitchButton = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorSwitchButton"));
	FloorSwitchButton->SetupAttachment(FloorSwitchBorder);

	if (ButtonReleasedMaterial)
	{
		FloorSwitchButton->SetMaterial(0, ButtonReleasedMaterial);
	}

	SwitchDelay = 2.f;
}

// Called when the game starts or when spawned
void AFloorSwitch::BeginPlay()
{
	Super::BeginPlay();
	
	InitialFloorSwitchPosition = FloorSwitchButton->GetComponentLocation();

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AFloorSwitch::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AFloorSwitch::OnOverlapEnd);
}

// Called every frame
void AFloorSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloorSwitch::ReleaseButton()
{
	if (OverlappingActors == 0)
	{
		bIsPressed = false;
		RaiseFloorSwitch();

		if (ButtonReleasedMaterial)
		{
			FloorSwitchButton->SetMaterial(0, ButtonReleasedMaterial);
		}
	}
}

bool AFloorSwitch::IsButtonPressed()
{
	return bIsPressed;
}

void AFloorSwitch::UpdateFloorSwitchPosition(float Z)
{
	FVector NewPosition = InitialFloorSwitchPosition;
	NewPosition.Z += Z;
	FloorSwitchButton->SetWorldLocation(NewPosition);
}

void AFloorSwitch::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OverlappingActors++;

	if (ButtonPressedMaterial)
	{
		FloorSwitchButton->SetMaterial(0, ButtonPressedMaterial);
	}

	bIsPressed = true;
	LowerFloorSwitch();
}

void AFloorSwitch::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OverlappingActors--;

	if (SwitchDelay > 0)
	{
		GetWorldTimerManager().SetTimer(SwitchHandle, this, &AFloorSwitch::ReleaseButton, SwitchDelay);
	}
	else
	{
		ReleaseButton();
	}
	
}