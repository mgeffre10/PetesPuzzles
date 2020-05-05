// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileReceiver.generated.h"

UCLASS()
class PUZZLEROOMS_API AProjectileReceiver : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileReceiver();

	// Trigger Volume
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Receiver")
	class UBoxComponent* TriggerVolume;

	// Static Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile Receiver")
	class UStaticMeshComponent* StaticMesh;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	bool bHasReceivedProjectile;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE bool HasReceivedProjectile() const { return bHasReceivedProjectile; }
	FORCEINLINE UBoxComponent* GetTriggerVolume() const { return TriggerVolume; }

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
