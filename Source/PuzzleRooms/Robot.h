// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Robot.generated.h"

UCLASS()
class PUZZLEROOMS_API ARobot : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARobot();

	// Static Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Robot")
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UBehaviorTree* BehaviorTree;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
