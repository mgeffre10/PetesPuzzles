// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMainPlayer::AMainPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// Controller rotation should only be used for camera, not the character
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Turn the character to the forward vector of the controller when moving
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);

	ZoomSpeed = 1500.f;
	MinZoomValue = 250.f;
	MaxZoomValue = 600.f;
}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*const FVector CameraLocation = FollowCamera->GetComponentLocation();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	FHitResult HitResult;
	
	GetWorld()->LineTraceSingleByObjectType(HitResult, CameraLocation, ForwardDirection * 1500.f, FCollisionObjectQueryParams::AllStaticObjects);
	//ActorLineTraceSingle(HitResult, CameraLocation, ForwardDirection * 1500.f, ECollisionChannel::ECC_Visibility, NULL);

	UE_LOG(LogTemp, Warning, TEXT("Actor Hit: %s"), *HitResult.GetActor()->GetFName().ToString());*/
}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMainPlayer::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMainPlayer::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("Zoom"), this, &AMainPlayer::ZoomInAndOut);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ACharacter::StopJumping);
}

void AMainPlayer::MoveForward(float Value)
{
	if (Controller && Value != 0.f)
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDirection, Value);
	}
}

void AMainPlayer::MoveRight(float Value)
{
	if (Controller && Value != 0.f)
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, Value);
	}
}

void AMainPlayer::ZoomInAndOut(float Value)
{

	if (Value != 0.f)
	{
		float DeltaArmLength = Value * ZoomSpeed * GetWorld()->GetDeltaSeconds();
		CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength += DeltaArmLength, MinZoomValue, MaxZoomValue);

		UE_LOG(LogTemp, Warning, TEXT("New Arm Length: %f"), CameraBoom->TargetArmLength);

	}
}