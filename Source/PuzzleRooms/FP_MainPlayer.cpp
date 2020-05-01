// Fill out your copyright notice in the Description page of Project Settings.


#include "FP_MainPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "PhysicsEngine/BodyInstance.h"
// Sets default values
AFP_MainPlayer::AFP_MainPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetRootComponent());
	FirstPersonCamera->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f));
	FirstPersonCamera->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void AFP_MainPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFP_MainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector CameraLocation = FirstPersonCamera->GetComponentLocation();
	const FVector ForwardVector = FirstPersonCamera->GetForwardVector();
	
	if (!bIsHoldingObject)
	{
		GetWorld()->LineTraceSingleByObjectType(HitResult, CameraLocation, CameraLocation + (ForwardVector * 500.f), ECollisionChannel::ECC_GameTraceChannel3);

		if (HitResult.bBlockingHit)
		{
			TracedObject = HitResult.GetActor();
			AInteractableObject* HitActor = Cast<AInteractableObject>(HitResult.GetActor());
			if (TracedObject != HitActor)
			{
				TracedObject = HitActor;
				UStaticMeshComponent* TracedObjectMeshComponent = Cast<UStaticMeshComponent>(TracedObject->GetComponentByClass(UStaticMeshComponent::StaticClass()));
				TracedObjectMeshComponent->SetRenderCustomDepth(true);
				TracedObjectMeshComponent->SetCustomDepthStencilValue(2);
			}
		}
		else
		{
			TracedObject = nullptr;
		}
	}
	else
	{
		if (HeldObjectRef)
		{
			HeldObjectRef->SetActorLocation(CameraLocation + (ForwardVector * 200.f));
		}
	}
}

// Called to bind functionality to input
void AFP_MainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AFP_MainPlayer::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AFP_MainPlayer::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction(TEXT("PickUp"), IE_Pressed, this, &AFP_MainPlayer::PickUpObject);
}

void AFP_MainPlayer::MoveForward(float Value)
{
	if (Value != 0.f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AFP_MainPlayer::MoveRight(float Value)
{
	if (Value != 0.f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AFP_MainPlayer::PickUpObject()
{
	if (!bIsHoldingObject)
	{
		if (TracedObject)
		{
			bIsHoldingObject = true;
			HeldObjectRef = TracedObject;
			HeldObjectRef->SetActorRotation(FRotator::ZeroRotator);
			HeldObjectStaticMesh = Cast<UStaticMeshComponent>(HeldObjectRef->GetComponentByClass(UStaticMeshComponent::StaticClass()));
			HeldObjectStaticMesh->SetEnableGravity(false);

			HeldObjectStaticMesh->BodyInstance.bLockXRotation = true;
			HeldObjectStaticMesh->BodyInstance.bLockYRotation = true;
			HeldObjectStaticMesh->BodyInstance.bLockZRotation = true;
		}
	}
	else
	{
		bIsHoldingObject = false;
		HeldObjectStaticMesh->SetEnableGravity(true);

		HeldObjectStaticMesh->BodyInstance.bLockXRotation = false;
		HeldObjectStaticMesh->BodyInstance.bLockYRotation = false;
		HeldObjectStaticMesh->BodyInstance.bLockZRotation = false;

		HeldObjectRef = nullptr;
	}
}
