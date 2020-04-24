// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "PMovingPlatform.generated.h"

// UENUM(BlueprintType)
// enum class EMS_MovementStyle : uint8 {
// 
// 	// Moves in Cirlce
// 	EMS_Circular		UMETA(DisplayName = "Circular Movement"),
// 	// Moves to Target point
// 	EMS_ToTargetPoint	UMETA(DisplayName = "To Taret Point"),
// 	// Moves smoothly up and down
// 	EMS_Sinusoid		UMETA(DisplayName = "Sinusoud on Z"),
// 	EMS_Default			UMETA(Hidden)
// };

/**
 * P(uzzle) Moving Platform.
 */
UCLASS()
class CODINGEXPERIENCE04_API APMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	
	APMovingPlatform();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	bool CheckCanMove();

	UFUNCTION(BlueprintCallable)
	void AddTrigger();

	UFUNCTION(BlueprintCallable)
	void RemoveTrigger();

protected:

	virtual void BeginPlay() override;

	void MovePlatformOverTime(float DeltaSeconds);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mobility, meta = ( UIMin = 1, ClampMin = 1 ))
	float MovementSpeed;

	/* How many triggers must be pressed to activate this Platform */
	UPROPERTY(EditAnywhere, Category = "Mobility|Trigger", meta = (UIMin = 0, ClampMin = 0))
	int32 RequiredTrigers;

	/* Specifies target location to which the platform is moving to */
	UPROPERTY(EditAnywhere, Category = Mobility, meta = (MakeEditWidget = true))
	FVector TargetLocation;

private:

	FVector Global_OriginLocation;
	FVector Global_TargetLocation;
	int32 ActiveTriggers;
};
