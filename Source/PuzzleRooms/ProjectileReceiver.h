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
	
public:	

	FORCEINLINE UBoxComponent* GetTriggerVolume() const { return TriggerVolume; }

};
