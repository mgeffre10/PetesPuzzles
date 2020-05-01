// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Furnace.generated.h"

UCLASS()
class PUZZLEROOMS_API AFurnace : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFurnace();

	// Box component for trigger volume
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Furnace")
	class UBoxComponent* TriggerVolume;
	
	// Static mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Furnace")
	class UStaticMeshComponent* StaticMesh;
	
	// Particle system for fire
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Furnace")
	class UParticleSystemComponent* FireParticleSystem;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
