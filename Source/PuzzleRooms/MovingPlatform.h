// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UENUM()
enum class EPlatformMovementType : uint8
{
	EPMT_Static				UMETA(DisplayName = "No Movement"),
	EPMT_Constant			UMETA(DisplayName = "Constant Movement"),
	EPMT_Projectile			UMETA(DisplayName = "Requires Projectile System"),
	EPMT_MAX				UMETA(DisplayName = "EPMT_MAX")
};

/**
 *
 * All Platforms apart from EPMT_Static must have a path of at least 2
 * All Platforms can have a timer on when they should move in the opposite direction
 * Only EPMT_Overlap cares about the player's position
 * Only EPMT_Projectile cares about a projectile system
 *
 */
UCLASS()
class PUZZLEROOMS_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

	/** Static Mesh */ 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Moving Platform")
	class UStaticMeshComponent* StaticMesh;

	/** Enum for Platform Movement Type */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moving Platform")
	TEnumAsByte<EPlatformMovementType> MovementType;
	
	/** Reference to Projectile System */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Moving Platform")
	class AProjectileSystem* ProjectileSystem;

	/** Array of FVectors to determine path */ 
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Moving Platform")
	TArray<FVector> PathVectors;

	/** Current Start Vector for Linear Interpolation */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Moving Platform")
	int32 CurrentStartVectorIndex;
	
	/** Current Destination Vector for Linear Interpolation */ 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Moving Platform")
	int32 CurrentDestinationVectorIndex;

	/** Tracking which direction in PathVectors array platform is going */
	UPROPERTY()
	bool bIsIteratingForward;

	UPROPERTY()
	bool bPlatformIsMoving;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moving Platform")
	bool bPlatformHasTimer;

	/** Timer value if bPlatformHasTimer is true */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moving Platform", meta = (ClampMin = 0, EditCondition = "bPlatformHasTimer"))
	int32 PlatformPauseTime;

	uint32 RemainingPauseTime;

	/** Timer Handle if bPlatformHasTimer is true */
	FTimerHandle PauseTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Function that take the Alpha value from the Alpha Timeline in order to execute Lerp */
	UFUNCTION(BlueprintCallable)
	void MovePlatform(float Alpha);

	/** Function to update the CurrentStartVectorIndex and CurrentDestinationVectorIndex */
	UFUNCTION(BlueprintCallable)
	void UpdateCurrentVectors();

	/** Function to start the Alpha Timeline for Linear Interpolation between two vectors */
	UFUNCTION(BlueprintImplementableEvent)
	void StartMovementLerp();

	/** Function to keep track of platform paused time */
	/** Function to determine if Platform has a path */
	UFUNCTION()
	FORCEINLINE bool PlatformHasPath() { return PathVectors.Num() > 1; }
};
