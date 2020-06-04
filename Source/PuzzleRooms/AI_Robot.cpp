// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Robot.h"
#include "GameFramework/Controller.h"
// Sets default values
AAI_Robot::AAI_Robot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void AAI_Robot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAI_Robot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAI_Robot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

