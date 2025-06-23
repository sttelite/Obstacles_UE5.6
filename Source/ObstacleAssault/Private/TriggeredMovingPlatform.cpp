// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggeredMovingPlatform.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

ATriggeredMovingPlatform::ATriggeredMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerZone"));
	TriggerZone->SetupAttachment(RootComponent);
	TriggerZone->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerZone->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerZone->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
        TriggerZone->InitBoxExtent(FVector(150.f, 150.f, 40.f));
}

void ATriggeredMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
    	AnchorLocation  = GetActorLocation();
	InitialVelocity = PlatformVelocity;                      
	TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &ATriggeredMovingPlatform::OnTriggerBegin);
    	TriggerZone->OnComponentEndOverlap.AddDynamic(this, &ATriggeredMovingPlatform::OnTriggerEnd);

}

void ATriggeredMovingPlatform::OnTriggerBegin(
	UPrimitiveComponent* /*OverlappedComponent*/,
	AActor*              OtherActor,
	UPrimitiveComponent* /*OtherComp*/,
	int32                /*OtherBodyIndex*/,
	bool                 /*bFromSweep*/,
	const FHitResult&    /*SweepResult*/)
{
	if (OtherActor && OtherActor->IsA<ACharacter>() && !bActive)
	{
		OverlapCount++;
		bActive = true;
		HalfCyclesDone = 0;
		PlatformVelocity = InitialVelocity;
        	StartLocation = AnchorLocation;
        	SetActorLocation(AnchorLocation);
	}
}

	void ATriggeredMovingPlatform::OnTriggerEnd(
		UPrimitiveComponent* /*OverlappedComponent*/,
		AActor*              OtherActor,
		UPrimitiveComponent* /*OtherComp*/,
		int32                /*BodyIndex*/)
	{
		if (!OtherActor || !OtherActor->IsA<ACharacter>()) return;

		OverlapCount = FMath::Max(OverlapCount - 1, 0);
	}

void ATriggeredMovingPlatform::Tick(float DeltaTime)
{
	if (!bActive) return;

	Super::Tick(DeltaTime);
	HalfCyclesDone++;

	if (ShouldPlatformReturn())
	{
		if (HalfCyclesDone >= 2){
			UE_LOG(LogTemp, Display, TEXT("Overlap count: %d"), OverlapCount);	
			StartLocation = AnchorLocation;
			HalfCyclesDone = 0;
			SetActorLocation(AnchorLocation);
			PlatformVelocity = InitialVelocity;
			if (OverlapCount == 0){
				bActive = false;
			}
		}
	}
}
