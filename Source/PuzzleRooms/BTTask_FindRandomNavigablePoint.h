// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindRandomNavigablePoint.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEROOMS_API UBTTask_FindRandomNavigablePoint : public UBTTaskNode
{
    GENERATED_BODY()

    UBTTask_FindRandomNavigablePoint();

public:

    // Destination Vector
    UPROPERTY(EditAnywhere, Category = "Blackboard")
    FBlackboardKeySelector DestinationVector;

    // Radius
    UPROPERTY(EditAnywhere, Category = "Parameters")
    float Radius;

public:

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
