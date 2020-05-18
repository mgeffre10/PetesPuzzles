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
	
	class APlayerController* PlayerController;
	FVector SourcePortalLocation;
	FVector DestinationPortalLocation;
	bool bCanTeleport;

	UPROPERTY(EditAnywhere, Category = "Portal System")
	float DestinationViewTest;

	UPROPERTY(EditAnywhere, Category = "Portal System")
	float SourceViewTest;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	float CalculatePortalView(APortalDoorway* TargetPortal);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
