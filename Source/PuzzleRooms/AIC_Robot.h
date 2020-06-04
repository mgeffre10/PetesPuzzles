// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"

#include "Perception/AIPerceptionTypes.h"

#include "AIC_Robot.generated.h"


/**
 * 
 */
UCLASS()
class PUZZLEROOMS_API AAIC_Robot : public AAIController
{
	GENERATED_BODY()

	AAIC_Robot();

public:

	// Sight Sense
	class UAISenseConfig_Sight* SightSense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sight Sense Configurations")
	float SightSense_SightRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sight Sense Configurations")
	float SightSense_LoseSightRadius;

	// OnPossess setup in blueprint as it has reference to BehaviorTree Asset
	
public:

	UFUNCTION()
	void OnTargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus);
};
