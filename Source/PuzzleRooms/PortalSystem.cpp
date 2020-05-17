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

	
	FRotator CameraRotation = PlayerController->PlayerCameraManager->GetTransformComponent()->GetComponentRotation();

	FRotator SourceView = CameraRotation;
	FRotator DestinationView = CameraRotation;

	SourceView.Yaw += CalculatePortalView(SourcePortal);
	DestinationView.Yaw += CalculatePortalView(DestinationPortal);

	DestinationPortal->GetPortal()->SetWorldRotation(CameraRotation + DestinationView);
	SourcePortal->GetPortal()->SetWorldRotation(CameraRotation + SourceView);
}

float APortalSystem::CalculatePortalView(APortalDoorway* TargetPortal)
{
	float SourcePortalYawRotation = SourcePortal->GetPortal()->GetComponentRotation().Yaw;
	float DestinationPortalYawRotation = DestinationPortal->GetPortal()->GetComponentRotation().Yaw;

	if (SourcePortalYawRotation == DestinationPortalYawRotation)
	{
		return 180.f;
	}
	else if (SourcePortalYawRotation + DestinationPortalYawRotation == 360.f)
	{
		return 0.f;
	}

	if (TargetPortal == SourcePortal)
	{
		if (SourcePortalYawRotation == 0 || DestinationPortalYawRotation == 0)
		{
			return DestinationPortalYawRotation - (180.f - SourcePortalYawRotation);
		}
		else
		{
			return SourcePortalYawRotation - DestinationPortalYawRotation;
		}
	}
	else if (TargetPortal == DestinationPortal)
	{
		if (SourcePortalYawRotation == 0 || DestinationPortalYawRotation == 0)
		{
			return SourcePortalYawRotation - (180.f - DestinationPortalYawRotation);
		}
		else
		{
			return DestinationPortalYawRotation - SourcePortalYawRotation;
		}
	}

	return 0.f;
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
						PlayerController->SetControlRotation(DestinationPortal->GetActorRotation());
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
						PlayerController->SetControlRotation(SourcePortal->GetActorRotation());
					}
				}
			}
			
		}
	}
	
}

void APortalSystem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

