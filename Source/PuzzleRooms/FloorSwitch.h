// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorSwitch.generated.h"

UCLASS()
class PUZZLEROOMS_API AFloorSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorSwitch();

	/** Component to handle overlap functionality */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Floor Switch")
	class UBoxComponent* TriggerVolume;

	/** Mesh for the floor switch */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Floor Switch")
	class UStaticMeshComponent* FloorSwitch;

	/** Mesh for the door */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Floor Switch")
	UStaticMeshComponent* Door;

	/** Initial door position when game begins */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Floor Switch")
	FVector InitialDoorPosition;

	/** Initial floor switch position when game begins */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Floor Switch")
	FVector InitialFloorSwitchPosition;

	/** Array for actors overlapping with the floor switch */
	int32 OverlappingActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor Switch")
	int32 SwitchDelay;

	FTimerHandle SwitchHandle;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void RaiseDoor();
	
	UFUNCTION(BlueprintImplementableEvent)
	void LowerDoor();
	
	void CloseDoor();

	UFUNCTION(BlueprintCallable)
	void UpdateDoorPosition(float Y);

	UFUNCTION(BlueprintImplementableEvent)
	void RaiseFloorSwitch();

	UFUNCTION(BlueprintImplementableEvent)
	void LowerFloorSwitch();

	UFUNCTION(BlueprintCallable)
	void UpdateFloorSwitchPosition(float Z);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
};
