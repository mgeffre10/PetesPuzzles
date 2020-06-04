// Fill out your copyright notice in the Description page of Project Settings.


#include "AIC_Robot.h"
#include "FP_MainPlayer.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"

AAIC_Robot::AAIC_Robot()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));

	SightSense_SightRadius = 1000.f;
	SightSense_LoseSightRadius = 1500.f;

	SightSense = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightSense"));
	SightSense->SightRadius = SightSense_SightRadius;
	SightSense->LoseSightRadius = SightSense_LoseSightRadius;
	SightSense->DetectionByAffiliation.bDetectNeutrals = true;

	PerceptionComponent->ConfigureSense(*SightSense);
	PerceptionComponent->SetDominantSense(SightSense->GetSenseImplementation());

	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAIC_Robot::OnTargetPerceptionUpdate);
}

void AAIC_Robot::OnTargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus)
{
	if (Cast<AFP_MainPlayer>(Actor))
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			GetBlackboardComponent()->SetValueAsObject(FName("TargetActor"), Actor);
		}
		else
		{
			GetBlackboardComponent()->SetValueAsObject(FName("TargetActor"), nullptr);
		}
		
	}
}