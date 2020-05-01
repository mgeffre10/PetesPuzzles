// Fill out your copyright notice in the Description page of Project Settings.


#include "Furnace.h"
#include "InteractableObject.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AFurnace::AFurnace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	RootComponent = TriggerVolume;

	TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerVolume->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	TriggerVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Overlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());

	FireParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireParticleSystem"));
	FireParticleSystem->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AFurnace::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AFurnace::OnOverlapBegin);
}

// Called every frame
void AFurnace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFurnace::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AInteractableObject* InteractableObj = Cast<AInteractableObject>(OtherActor);

		if (InteractableObj)
		{
			InteractableObj->bIsDestroyed = true;
			InteractableObj->Destroy();
		}
	}
}
