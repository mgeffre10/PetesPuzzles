// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/Material.h"
#include "StandaloneButton.generated.h"

UCLASS()
class PUZZLEROOMS_API AStandaloneButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStandaloneButton();

	// Trigger Volume
	UPROPERTY(VisibleAnywhere, Category = "Standalone Button")
	class UBoxComponent* TriggerVolume;

	// Static Mesh
	UPROPERTY(VisibleAnywhere, Category = "Standalone Button")
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Standalone Button")
	class UMaterial* OutOfRangeMaterial;

	UPROPERTY(EditAnywhere, Category = "Standalone Button")
	class UMaterial* InRangeMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UBoxComponent* GetTriggerVolume() const { return TriggerVolume; }
	FORCEINLINE UStaticMeshComponent* GetStaticMesh() const { return StaticMesh; }
	FORCEINLINE void SetMaterialToInRange() { StaticMesh->SetMaterial(2, InRangeMaterial); }
	FORCEINLINE void SetMaterialToOutOfRange() { StaticMesh->SetMaterial(2, OutOfRangeMaterial); }
};
