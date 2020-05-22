// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot_AIController.h"
#include "Robot.h"
#include "BehaviorTree/BehaviorTree.h"

void ARobot_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ARobot* RobotAI = Cast<ARobot>(InPawn);

	if (RobotAI)
	{
		UBehaviorTree* BehaviorTree = RobotAI->BehaviorTree;
		
		if (BehaviorTree)
		{
			RunBehaviorTree(BehaviorTree);
		}
	}
}
