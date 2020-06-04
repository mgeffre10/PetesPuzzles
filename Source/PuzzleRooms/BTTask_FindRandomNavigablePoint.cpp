// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomNavigablePoint.h"

#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTTask_FindRandomNavigablePoint::UBTTask_FindRandomNavigablePoint()
{
	Radius = 300.f;
}

EBTNodeResult::Type UBTTask_FindRandomNavigablePoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	// Blackboard
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	// AI Pawn
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();

	// Navigation System
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	if (!Blackboard || !ControlledPawn || !NavSystem)
	{
		return EBTNodeResult::Failed;
	}

	FNavLocation Result;
	FVector Origin = ControlledPawn->GetActorLocation();

	bool bSuccessfulQuery = NavSystem->GetRandomReachablePointInRadius(Origin, Radius, Result);

	if (!bSuccessfulQuery)
	{
		return EBTNodeResult::Failed;
	}

	Blackboard->SetValueAsVector(DestinationVector.SelectedKeyName, Result.Location);

	return EBTNodeResult::Succeeded;
}