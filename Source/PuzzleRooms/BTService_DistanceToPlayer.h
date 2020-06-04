// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_DistanceToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEROOMS_API UBTService_DistanceToPlayer : public UBTService
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector TargetActor;
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector Distance;

public:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
