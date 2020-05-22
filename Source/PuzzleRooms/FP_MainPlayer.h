// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FP_MainPlayer.generated.h"

UCLASS()
class PUZZLEROOMS_API AFP_MainPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFP_MainPlayer();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* FirstPersonCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactions")
	bool bIsHoldingObject;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactions")
	class AInteractableObject* HeldObjectRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactions")
	class UStaticMeshComponent* HeldObjectStaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Portals")
	bool bIsOverlappingButtonVolume;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Portals")
	class APortalSystem* PortalSystemReference;

	AInteractableObject* TracedObject;

	FHitResult HitResult;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE void SetPortalSystemReference(APortalSystem* PortalSystem) { PortalSystemReference = PortalSystem; }
	FORCEINLINE APortalSystem* GetPortalSystemReference() const { return PortalSystemReference; }

	FORCEINLINE void SetIsOverlappingButtonVolume(bool IsOverlapping) { bIsOverlappingButtonVolume = IsOverlapping; }
	FORCEINLINE bool GetIsOverlappingButtonVolume() const { return bIsOverlappingButtonVolume; }

	void MoveForward(float Value);
	void MoveRight(float Value);
	void PickUpObject();
	void DetermineInteraction();
};
