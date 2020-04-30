// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorSwitch.h"
#include "Door.generated.h"

UENUM()
enum class EDoorRequirement : uint8 {
	EDR_FloorSwitches		UMETA(DisplayName = "Floor Switches"),
	EDR_ActorDestruction	UMETA(DisplayName = "Actor Destruction"),
	EDR_Position			UMETA(DisplayName = "Position"),
	EDR_MAX					UMETA(DisplayName = "EDR MAX")
};

UCLASS()
class PUZZLEROOMS_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	/** Mesh for the door */ 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* StaticMesh;

	/** Initial door position when game begins */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	FVector InitialDoorPosition;

	/** Store requirement to open door based on EDoorRequirement enum */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Requirements")
	TEnumAsByte<EDoorRequirement> DoorRequirement;
	
	/** Pointer reference to actor that needs to be destroyed if requirement is EDR_ActorDestruction */ 
	UPROPERTY(EditInstanceOnly, Category = "Door Requirements")
	TArray<AActor*> ActorsToBeDestroyed;

	/** TArray to floor switch actors if requirement is EDR_FloorSwitches */ 
	UPROPERTY(EditInstanceOnly, Category = "Door Requirements")
	TArray<AFloorSwitch*> FloorSwitches;

	/** Position range if requirement is EDR_Position */ 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function called in tick to check requirements based on enum
	void CheckDoorRequirements();

	// Function called when requirements from above function are satisfied
	UFUNCTION(BlueprintImplementableEvent)
	void OpenDoor();

	UFUNCTION(BlueprintImplementableEvent)
	void CloseDoor();

	UFUNCTION(BlueprintCallable)
	void UpdateDoorPosition(float Z);

	void ShutDoor();

};
