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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom Properties")
	class UBoxComponent* TriggerVolume;

	/** Mesh for the floor switch */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Custom Properties")
	class UStaticMeshComponent* FloorSwitchBorder;

	/** Mesh for the floor switch */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Custom Properties")
	class UStaticMeshComponent* FloorSwitchButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Properties")
	class UMaterial* ButtonReleasedMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Properties")
	UMaterial* ButtonPressedMaterial;

	/** Initial floor switch position when game begins */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Custom Properties")
	FVector InitialFloorSwitchPosition;

	/** Array for actors overlapping with the floor switch */
	int32 OverlappingActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Properties")
	int32 SwitchDelay;

	FTimerHandle SwitchHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Custom Properties")
	bool bIsPressed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void RaiseFloorSwitch();

	UFUNCTION(BlueprintImplementableEvent)
	void LowerFloorSwitch();

	UFUNCTION(BlueprintCallable)
	void UpdateFloorSwitchPosition(float Z);

	void ReleaseButton();

	bool IsButtonPressed();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
