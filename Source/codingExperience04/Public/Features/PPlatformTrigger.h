// All rights reserved Dominik Pavlicek

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPlatformTrigger.generated.h"

class APMovingPlatform;
class UBillboardComponent;
class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class CODINGEXPERIENCE04_API APPlatformTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPlatformTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void NotifyBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void NotifyEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:

	UPROPERTY(VisibleAnywhere, Category = "Platform")
	UBoxComponent* BoxComp = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Platform")
	UStaticMeshComponent* MeshComp = nullptr;

	UPROPERTY(EditInstanceOnly, Category = "Platform")
	TArray<APMovingPlatform*> AffectedPlatforms;

private:
	UPROPERTY()
	UBillboardComponent* BillboardComp;
};
