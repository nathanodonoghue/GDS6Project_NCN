// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "TriggerEventMove.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTPROJECTGDS6_API UTriggerEventMove : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerEventMove();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void MoveObject(float DeltaTime);
	void MoveObjectBack(float DeltaTime);
		
private:
	float InitialYPos;
	float InitialXPos;
	float CurrentYPos;
	float CurrentXPos;

	UPROPERTY(EditAnywhere)
		float TargetYPos = 0.f;

	UPROPERTY(EditAnywhere)
		float TargetXPos = 0.f;

	float ObjectLastMoved = 0.f;

	UPROPERTY(EditAnywhere)
		float ObjectMoveBackDelay = 2.f;

	UPROPERTY(EditAnywhere)
		float ObjectMoveBackSpeed = 2.f;

	UPROPERTY(EditAnywhere)
		float ObjectMoveSpeed = 1.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
		AActor* TriggerActor;
};