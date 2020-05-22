// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Robot_AIController.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEROOMS_API ARobot_AIController : public AAIController
{
	GENERATED_BODY()
	
protected:

	void OnPossess(APawn* InPawn) override;

};
