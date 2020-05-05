// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class PUZZLEROOMS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Static Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile")
	class UStaticMeshComponent* StaticMesh;

	// Projectile Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float ProjectileSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	bool bShouldMove;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UStaticMeshComponent* GetStaticMesh() { return StaticMesh; }
	FORCEINLINE float GetProjectileSpeed() const { return ProjectileSpeed; }
	FORCEINLINE bool GetProjectileShouldMove() const { return bShouldMove; }
	FORCEINLINE void SetProjectileShouldMove(bool Value) { bShouldMove = Value; }

	void MoveProjectile(float DeltaTime);
};
