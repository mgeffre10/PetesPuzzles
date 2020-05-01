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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Liftables")
	bool bIsHoldingObject;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Liftables")
	class AInteractableObject* HeldObjectRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Liftables")
	class UStaticMeshComponent* HeldObjectStaticMesh;

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

	void MoveForward(float Value);
	void MoveRight(float Value);
	void PickUpObject();
};
