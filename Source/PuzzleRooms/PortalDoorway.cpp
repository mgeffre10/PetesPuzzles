// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalDoorway.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SceneComponent.h"
#include "Engine/TextureRenderTarget2D.h"

// Sets default values
APortalDoorway::APortalDoorway()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	TriggerVolume->SetupAttachment(GetRootComponent());

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	FrameMesh->SetupAttachment(GetRootComponent());

	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
	PortalMesh->SetupAttachment(FrameMesh);

	PortalMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	PortalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	Portal = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Portal"));
	Portal->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void APortalDoorway::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APortalDoorway::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

