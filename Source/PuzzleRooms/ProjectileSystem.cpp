// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileSystem.h"
#include "ProjectileShooter.h"
#include "ProjectileReceiver.h"
#include "Projectile.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"


// Sets default values
AProjectileSystem::AProjectileSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	ProjectileDecayTimer = 3.f;
	ProjectileSpeed = 300.f;
}

// Called when the game starts or when spawned
void AProjectileSystem::BeginPlay()
{
	Super::BeginPlay();
	
	if (!ProjectileShooter || !ProjectileReceiver)
	{
		bShouldContinueShooting = false;
	}
	else
	{
		bShouldContinueShooting = true;
	}

	ShooterSpawnVolume = ProjectileShooter->GetSpawnVolume();

	if (bShouldContinueShooting)
	{
		SpawnProjectile();
		Projectile->SetProjectileShouldMove(true);
	}
}

// Called every frame
void AProjectileSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bShouldContinueShooting)
	{
		Projectile->SetProjectileShouldMove(false);
		Projectile->SetActorLocation(ProjectileReceiver->GetTriggerVolume()->GetComponentLocation());
	}
	else
	{
		CheckShouldContinueShooting();
	}
}

void AProjectileSystem::CheckShouldContinueShooting()
{
	bShouldContinueShooting = !ProjectileReceiver->HasReceivedProjectile();

}

void AProjectileSystem::SpawnProjectile()
{
	const FVector SpawnLocation = ShooterSpawnVolume->GetComponentLocation();

	Projectile = GetWorld()->SpawnActor<AProjectile>(ActorToSpawn, SpawnLocation, ShooterSpawnVolume->GetComponentRotation());
	Projectile->SetProjectileSpeed(ProjectileSpeed);

	if (ProjectileDecayTimer > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectileSystem::DestroyProjectile, ProjectileDecayTimer, false);
	}
}

void AProjectileSystem::DestroyProjectile()
{
	UE_LOG(LogTemp, Warning, TEXT("DestroyProjectile called"));
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	Projectile->Destroy();
	SpawnProjectile();
}