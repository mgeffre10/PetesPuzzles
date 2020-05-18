// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalSystem.h"
#include "PortalDoorway.h"
#include "FP_MainPlayer.h"

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
	bCanTeleport = true;
}

// Called when the game starts or when spawned
void APortalSystem::BeginPlay()
{
	Super::BeginPlay();
	
	// Get Player Controller
	PlayerController = GetWorld()->GetFirstPlayerController();

	// Subtract Source and Destination Portal Location vectors
	SourcePortalLocation = SourcePortal->GetRootComponent()->GetComponentLocation();
	DestinationPortalLocation = DestinationPortal->GetRootComponent()->GetComponentLocation();

	SourcePortal->GetPortalMesh()->OnComponentBeginOverlap.AddDynamic(this, &APortalSystem::OnOverlapBegin);
	DestinationPortal->GetPortalMesh()->OnComponentBeginOverlap.AddDynamic(this, &APortalSystem::OnOverlapBegin);
}

// Called every frame
void APortalSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FVector CameraLocation = PlayerController->PlayerCameraManager->GetTransformComponent()->GetComponentLocation();
	FRotator CameraRotation = PlayerController->PlayerCameraManager->GetTransformComponent()->GetComponentRotation();

	/*SourcePortal->GetPortal()->SetWorldLocation((SourcePortal->GetPortal()->GetComponentLocation() - DestinationPortal->GetPortal()->GetComponentLocation()) + CameraLocation);
	DestinationPortal->GetPortal()->SetWorldLocation((DestinationPortal->GetPortal()->GetComponentLocation() - SourcePortal->GetPortal()->GetComponentLocation()) + CameraLocation);*/
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

	UE_LOG(LogTemp, Warning, TEXT("Adjustment Value: %f"), AdjustmentValue);
	return AdjustmentValue;
}

void APortalSystem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap in PortalSystem occured."));

	if (bCanTeleport)
	{
		bCanTeleport = false;
		//PlayerController->GetOwner()->SetActorLocation();
	}

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

void APortalSystem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

