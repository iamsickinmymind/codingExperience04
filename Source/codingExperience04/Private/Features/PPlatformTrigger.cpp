// All rights reserved Dominik Pavlicek

#include "PPlatformTrigger.h"

#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticmeshComponent.h"

#include "Features/PMovingPlatform.h"

// Sets default values
APPlatformTrigger::APPlatformTrigger()
{

	BoxComp = CreateDefaultSubobject<UBoxComponent>(FName("BoxComponent"));
	RootComponent = BoxComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("MeshComponent"));
	MeshComp->SetupAttachment(GetRootComponent());
	   	
	BillboardComp = CreateDefaultSubobject<UBillboardComponent>(FName("BillboardComp"));
	BillboardComp->SetupAttachment(GetRootComponent());
	
	SetReplicates(true);

	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void APPlatformTrigger::BeginPlay()
{
	Super::BeginPlay();

	if (BoxComp) {

		BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APPlatformTrigger::NotifyBeginOverlap);
		BoxComp->OnComponentEndOverlap.AddDynamic(this, &APPlatformTrigger::NotifyEndOverlap);
	}
}

void APPlatformTrigger::NotifyBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {

	for (auto ItrPlatform : AffectedPlatforms) {

		if (ItrPlatform) ItrPlatform->AddTrigger();
	}
}

void APPlatformTrigger::NotifyEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {

	for (auto ItrPlatform : AffectedPlatforms) {

		if (ItrPlatform) ItrPlatform->RemoveTrigger();
	}
}