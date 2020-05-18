// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalSystem.generated.h"

UCLASS()
class PUZZLEROOMS_API APortalSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortalSystem();

	// Reference to Source Portal BP
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Portal System")
	class APortalDoorway* SourcePortal;

	// Reference to Destination Portal BP
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Portal System")
	class APortalDoorway* DestinationPortal;

	// Reference to Standalone Button
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Portal System")
	class AStandaloneButton* PortalControlButton;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Portal System")
	TArray<FVector> DestinationPortalLocations;

	UPROPERTY(VisibleAnywhere, Category = "Portal System")
	int32 CurrentDestinationIndex;

	class APlayerController* PlayerController;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	float CalculatePortalView(APortalDoorway* TargetPortal);

	UFUNCTION()
	void OnPortalOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnButtonOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnButtonOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void UpdatePortalDestination();
};
