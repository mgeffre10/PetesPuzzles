// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_DistanceToPlayer.h"

#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_DistanceToPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	
	if (!Blackboard || !ControllingPawn)
	{
		return;
	}

	AActor* Target = Cast<AActor>(Blackboard->GetValueAsObject(TargetActor.SelectedKeyName));

	if (!Target)
	{
		return;
	}

	FVector DeltaVector = ControllingPawn->GetActorLocation() - Target->GetActorLocation();

	Blackboard->SetValueAsFloat(Distance.SelectedKeyName, DeltaVector.Size());
}