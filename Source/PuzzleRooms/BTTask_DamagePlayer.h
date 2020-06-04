// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_DamagePlayer.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEROOMS_API UBTTask_DamagePlayer : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_DamagePlayer();

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector TargetActor;

	UPROPERTY(EditAnywhere, Category = "Parameters")
	float DamageAmount;

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
