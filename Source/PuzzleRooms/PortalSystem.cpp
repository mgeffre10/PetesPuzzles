// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalSystem.h"
#include "PortalDoorway.h"
#include "FP_MainPlayer.h"
#include "StandaloneButton.h"

#include "Components/BoxComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values
APortalSystem::APortalSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APortalSystem::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerController = GetWorld()->GetFirstPlayerController();

	// Ensure Destination Portal starting position is first element
	DestinationPortalLocations.Insert(DestinationPortal->GetActorLocation(), 0);

	CurrentDestinationIndex = 0;

	SourcePortal->GetPortalMesh()->OnComponentBeginOverlap.AddDynamic(this, &APortalSystem::OnPortalOverlapBegin);
	DestinationPortal->GetPortalMesh()->OnComponentBeginOverlap.AddDynamic(this, &APortalSystem::OnPortalOverlapBegin);

	PortalControlButton->GetTriggerVolume()->OnComponentBeginOverlap.AddDynamic(this, &APortalSystem::OnButtonOverlapBegin);
	PortalControlButton->GetTriggerVolume()->OnComponentEndOverlap.AddDynamic(this, &APortalSystem::OnButtonOverlapEnd);
}

// Called every frame
void APortalSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator CameraRotation = PlayerController->PlayerCameraManager->GetTransformComponent()->GetComponentRotation();

	FRotator SourceView = CameraRotation;
	FRotator DestinationView = CameraRotation;

	SourceView.Yaw += CalculatePortalView(DestinationPortal);
	DestinationView.Yaw += CalculatePortalView(SourcePortal);

	DestinationPortal->GetPortal()->SetWorldRotation(DestinationView);
	SourcePortal->GetPortal()->SetWorldRotation(SourceView);
}

float APortalSystem::CalculatePortalView(APortalDoorway* TargetPortal)
{
	float SourcePortalYawRotation = SourcePortal->GetActorRotation().Yaw;
	float DestinationPortalYawRotation = DestinationPortal->GetActorRotation().Yaw;

	float AdjustmentValue = 0.f;

	if (SourcePortalYawRotation == DestinationPortalYawRotation)
	{
		AdjustmentValue = 180.f;
	}
	else if (FMath::CeilToInt(FMath::Abs(SourcePortalYawRotation - DestinationPortalYawRotation)) == 180.f)
	{
		// Keep return value at 0.f
	}
	else
	{
		if (TargetPortal == SourcePortal)
		{
			AdjustmentValue = SourcePortalYawRotation - DestinationPortalYawRotation;
		}
		else
		{
			AdjustmentValue = DestinationPortalYawRotation - SourcePortalYawRotation;
		}
	}

	return AdjustmentValue;
}

void APortalSystem::OnPortalOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (SweepResult.GetActor())
	{
		APortalDoorway* Portal = Cast<APortalDoorway>(SweepResult.GetActor());

		if (Portal)
		{
			if (Portal == SourcePortal)
			{

				FVector DestinationPortalForwardVector = DestinationPortal->GetActorForwardVector();
				
				if (OtherActor)
				{
					AFP_MainPlayer* Player = Cast<AFP_MainPlayer>(OtherActor);

					if (Player)
					{
						FVector NewLocation = DestinationPortal->GetActorLocation() + (DestinationPortalForwardVector * 100.f);
						
						Player->SetActorLocation(NewLocation);
						PlayerController->SetControlRotation(FRotator(PlayerController->GetControlRotation().Pitch, DestinationPortal->GetActorRotation().Yaw, PlayerController->GetControlRotation().Roll));
					}
				}
			}
			else
			{
				FVector SourcePortalForwardVector = SourcePortal->GetActorForwardVector();

				if (OtherActor)
				{
					AFP_MainPlayer* Player = Cast<AFP_MainPlayer>(OtherActor);

					if (Player)
					{
						FVector NewLocation = SourcePortal->GetActorLocation() + (SourcePortalForwardVector * 100.f);

						Player->SetActorLocation(NewLocation);
						PlayerController->SetControlRotation(FRotator(PlayerController->GetControlRotation().Pitch, SourcePortal->GetActorRotation().Yaw, PlayerController->GetControlRotation().Roll));

					}
				}
			}
			
		}
	}
	
}

void APortalSystem::OnButtonOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AFP_MainPlayer* Player = Cast<AFP_MainPlayer>(OtherActor);

		if (Player)
		{
			Player->SetIsOverlappingButtonVolume(true);
			Player->SetPortalSystemReference(this);

			PortalControlButton->SetMaterialToInRange();
		}
	}
}

void APortalSystem::OnButtonOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		AFP_MainPlayer* Player = Cast<AFP_MainPlayer>(OtherActor);

		if (Player)
		{
			Player->SetIsOverlappingButtonVolume(false);
			Player->SetPortalSystemReference(nullptr);

			PortalControlButton->SetMaterialToOutOfRange();
		}
	}
}

void APortalSystem::UpdatePortalDestination()
{
	CurrentDestinationIndex = (CurrentDestinationIndex + 1) % DestinationPortalLocations.Num();
	DestinationPortal->SetActorLocation(DestinationPortalLocations[CurrentDestinationIndex]);
}