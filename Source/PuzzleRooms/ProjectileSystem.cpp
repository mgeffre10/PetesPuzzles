// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileSystem.h"
#include "ProjectileShooter.h"
#include "ProjectileReceiver.h"
#include "Projectile.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"


// Sets default values
AProjectileSystem::AProjectileSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	ProjectileDecayTimer = 0.f;
	ProjectileSpeed = 100000.f;

	bHasSystemCompleted = false;
}

// Called when the game starts or when spawned
void AProjectileSystem::BeginPlay()
{
	Super::BeginPlay();
	
	if (ProjectileShooter && ProjectileReceiver && ActorToSpawn)
	{
		SpawnProjectile();
		AddForceToProjectile(Projectile->GetActorForwardVector(), Projectile->GetStaticMesh());

		ProjectileReceiver->GetTriggerVolume()->OnComponentBeginOverlap.AddDynamic(this, &AProjectileSystem::OnOverlapBegin);
	}
}

void AProjectileSystem::SpawnProjectile()
{
	if (!HasSystemCompleted())
	{
		const UBoxComponent* SpawnVolume = ProjectileShooter->GetSpawnVolume();
		const FVector SpawnLocation = SpawnVolume->GetComponentLocation();
		const FRotator SpawnRotation = SpawnVolume->GetComponentRotation();

		Projectile = GetWorld()->SpawnActor<AProjectile>(ActorToSpawn, SpawnLocation, SpawnRotation);
		Projectile->OnActorHit.AddDynamic(this, &AProjectileSystem::OnHit);

		if (ProjectileDecayTimer > 0)
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectileSystem::DestroyProjectile, ProjectileDecayTimer, false);
		}
	}
}

void AProjectileSystem::DestroyProjectile()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	if (!HasSystemCompleted())
	{
		Projectile->Destroy();
		SpawnProjectile();
		AddForceToProjectile(Projectile->GetActorForwardVector(), Projectile->GetStaticMesh());
	}
}

void AProjectileSystem::AddForceToProjectile(FVector Direction, UStaticMeshComponent* Mesh)
{
	Mesh->AddForce(Direction * ProjectileSpeed);
}

void AProjectileSystem::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit Impact Normal: %s"), *Hit.ImpactNormal.ToString());

	AProjectile* CollidingActor = Cast<AProjectile>(SelfActor);

	if (CollidingActor)
	{
		AddForceToProjectile(Hit.ImpactNormal, CollidingActor->GetStaticMesh());
	}
}

void AProjectileSystem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin() called on ProjectileReceiver"));

	if (OtherActor)
	{
		AProjectile* OverlappingActor = Cast<AProjectile>(OtherActor);

		if (OverlappingActor == Projectile)
		{
			UE_LOG(LogTemp, Warning, TEXT("CollidingActor is Projectile"));
			bHasSystemCompleted = true;
			Projectile->GetStaticMesh()->SetSimulatePhysics(false);
			Projectile->GetStaticMesh()->SetWorldLocation(ProjectileReceiver->GetTriggerVolume()->GetComponentLocation());
		}
	}
}