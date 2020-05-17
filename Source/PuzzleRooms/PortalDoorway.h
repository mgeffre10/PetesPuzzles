// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalDoorway.generated.h"

UCLASS()
class PUZZLEROOMS_API APortalDoorway : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortalDoorway();

	// Trigger Volume
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Poral Doorway")
	class UBoxComponent* TriggerVolume;

	// Door Frame static mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Poral Doorway")
	class UStaticMeshComponent* FrameMesh;

	// Portal mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Portal Doorway")
	UStaticMeshComponent* PortalMesh;

	// Doorway scene
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Poral Doorway")
	class USceneCaptureComponent2D* Portal;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE USceneCaptureComponent2D* GetPortal() const { return Portal; }
	FORCEINLINE UBoxComponent* GetTriggerVolume() const { return TriggerVolume; }
	FORCEINLINE UStaticMeshComponent* GetPortalMesh() const { return PortalMesh; }
};
