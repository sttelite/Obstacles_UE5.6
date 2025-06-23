// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ObstacleAssault/MovingPlatform.h"
#include "TriggeredMovingPlatform.generated.h"

class UBoxComponent;

UCLASS()
class OBSTACLEASSAULT_API ATriggeredMovingPlatform : public AMovingPlatform
{
	GENERATED_BODY()

public:
	ATriggeredMovingPlatform();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	

	UPROPERTY(VisibleAnywhere, Category = "Trigger")
	UBoxComponent* TriggerZone;

	bool bActive = false;
	int32 OverlapCount = 0;
    	FVector AnchorLocation; 
	int32 HalfCyclesDone = 0;

	UFUNCTION()
	void OnTriggerBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor*              OtherActor,
		UPrimitiveComponent* OtherComp,
		int32                OtherBodyIndex,
		bool                 bFromSweep,
		const FHitResult&    SweepResult);

	UFUNCTION()
	void OnTriggerEnd(
    	UPrimitiveComponent* OverlappedComponent,
    	AActor*              OtherActor,
    	UPrimitiveComponent* OtherComp,
    	int32                OtherBodyIndex);

private:
	FVector InitialVelocity;
};
