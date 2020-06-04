// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_DamagePlayer.h"
#include "FP_MainPlayer.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_DamagePlayer::UBTTask_DamagePlayer()
{
	DamageAmount = 10.f;
}

EBTNodeResult::Type UBTTask_DamagePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (!Blackboard)
	{
		return EBTNodeResult::Failed;
	}

	AFP_MainPlayer* Player = Cast<AFP_MainPlayer>(Blackboard->GetValueAsObject(TargetActor.SelectedKeyName));

	if (!Player)
	{
		return EBTNodeResult::Failed;
	}

	Player->ReduceHealth(DamageAmount);

	return EBTNodeResult::Succeeded;
}