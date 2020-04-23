// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEROOMS_API UMainPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsInAir;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsClimbing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsPushing;*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	APawn* Pawn;
	
	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties();
};
