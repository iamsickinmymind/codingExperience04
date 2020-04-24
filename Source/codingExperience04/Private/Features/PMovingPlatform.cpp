// Fill out your copyright notice in the Description page of Project Settings.

#include "PMovingPlatform.h"

APMovingPlatform::APMovingPlatform() {

	PrimaryActorTick.bCanEverTick = true;

	//bStaticMeshReplicateMovement = true;

	SetReplicates(true);
	SetReplicateMovement(true);
	
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);

	MovementSpeed = 10.f;
	RequiredTrigers = 1;
}

void APMovingPlatform::BeginPlay() {

	Super::BeginPlay();

	Global_OriginLocation = GetActorLocation();
	Global_TargetLocation = GetTransform().TransformPositionNoScale(TargetLocation);
}

void APMovingPlatform::Tick(float DeltaSeconds) {

	Super::Tick(DeltaSeconds);

	if (Role == ROLE_Authority && CheckCanMove()) {

		MovePlatformOverTime(DeltaSeconds);
	}
}

void APMovingPlatform::MovePlatformOverTime(float DeltaSeconds)
{
	FVector NewLocation = GetActorLocation();

	float MovementLenght = (Global_TargetLocation - Global_OriginLocation).Size();

	float MovementTraveled = (NewLocation - Global_OriginLocation).Size();

	if (MovementTraveled > MovementLenght) {

		FVector TempVector = Global_TargetLocation;

		Global_TargetLocation = Global_OriginLocation;

		Global_OriginLocation = TempVector;
	}

	FVector Direction = (Global_TargetLocation - Global_OriginLocation).GetSafeNormal();

	NewLocation += MovementSpeed * Direction * DeltaSeconds;

	SetActorLocation(NewLocation);
}

bool APMovingPlatform::CheckCanMove() {

	return ActiveTriggers >= RequiredTrigers;
}

void APMovingPlatform::AddTrigger() {

	ActiveTriggers++;
}

void APMovingPlatform::RemoveTrigger() {

	if (ActiveTriggers > 0) ActiveTriggers--;
}