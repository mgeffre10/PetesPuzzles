// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileSystem.generated.h"

UCLASS()
class PUZZLEROOMS_API AProjectileSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileSystem();

	// Reference to ProjectileShooter
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Projectile System")
	class AProjectileShooter* ProjectileShooter;

	// Reference to ProjectileReceiver
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Projectile System")
	class AProjectileReceiver* ProjectileReceiver;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile System")
	TSubclassOf<class AProjectile> ActorToSpawn;

	// Reference to Projectile
	AProjectile* Projectile;

	FTimerHandle TimerHandle;

	// Time for Projectile Decay
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile System")
	int ProjectileDecayTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile System")
	float ProjectileSpeed;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	bool bHasSystemCompleted;

public:	
	UFUNCTION()
	void SpawnProjectile();

	UFUNCTION()
	void DestroyProjectile();

	UFUNCTION()
	void AddForceToProjectile(FVector Direction, UStaticMeshComponent* Target);

	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FORCEINLINE bool HasSystemCompleted() { return bHasSystemCompleted; }
};
