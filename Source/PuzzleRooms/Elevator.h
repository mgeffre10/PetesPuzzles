// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Elevator.generated.h"

UCLASS()
class PUZZLEROOMS_API AElevator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevator();
	
	// Trigger Volume
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Elevator")
	class UBoxComponent* TriggerVolume;

	// Static Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Elevator")
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Elevator")
	FVector InitialElevatorPosition;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void RaiseElevator();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OpenElevatorDoors();

	UFUNCTION(BlueprintImplementableEvent)
	void CloseElevatorDoors();

	UFUNCTION(BlueprintCallable)
	void UpdateElevatorPosition(float Z);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
