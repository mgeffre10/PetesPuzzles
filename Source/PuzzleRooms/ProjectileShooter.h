// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileShooter.generated.h"

UCLASS()
class PUZZLEROOMS_API AProjectileShooter : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AProjectileShooter();

	// Spawn Volume
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Shooter")
	class UBoxComponent* SpawnVolume;

	// Static Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile Shooter")
	class UStaticMeshComponent* StaticMesh;

	FORCEINLINE UBoxComponent* GetSpawnVolume() const { return SpawnVolume; }
};
