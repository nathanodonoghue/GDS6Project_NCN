// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerEventMove.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UTriggerEventMove::UTriggerEventMove()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTriggerEventMove::BeginPlay()
{
	Super::BeginPlay();

	InitialYPos = GetOwner()->GetActorLocation().Y;
	CurrentYPos = InitialYPos;
	TargetYPos += InitialYPos;

	InitialXPos = GetOwner()->GetActorLocation().X;
	CurrentXPos = InitialXPos;
	TargetXPos += InitialXPos;

	if (!PressurePlate)
	{
		UE_LOG(Log_Temp, Error, TEXT("%s has the trigger event mov e component on it, but has no trigger volume assigned"), *GetOwner()->GetName());
	}
	
	TriggerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UTriggerEventMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && PressurePlate->IsOverlappingActor(TriggerActor))
	{
		MoveObject(DeltaTime);
		ObjectLastMoved = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - ObjectLastMoved > ObjectMoveBackDelay)
		{
			MoveObjectBack(DeltaTime);
		}
	}
}

void UTriggerEventMove::MoveObject(float DeltaTime) 
{
	CurrentYPos = FMath::Lerp(CurrentYPos, TargetYPos, DeltaTime * ObjectMoveSpeed);
	CurrentXPos = FMath::Lerp(CurrentXPos, TargetXPos, DeltaTime * ObjectMoveSpeed);
	FVector ObjectPosition = GetOwner()->GetActorLocation();
	ObjectPosition.Y = CurrentYPos;
	ObjectPosition.X = CurrentXPos;
	GetOwner()->SetActorLocation(ObjectPosition);
}

void UTriggerEventMove::MoveObjectBack(float DeltaTime) 
{
	CurrentYPos = FMath::Lerp(CurrentYPos, InitialYPos, DeltaTime * ObjectMoveBackSpeed);
	CurrentXPos = FMath::Lerp(CurrentXPos, InitialXPos, DeltaTime * ObjectMoveBackSpeed);
	FVector ObjectPosition = GetOwner()->GetActorLocation();
	ObjectPosition.Y = CurrentYPos;
	ObjectPosition.X = CurrentXPos;
	GetOwner()->SetActorLocation(ObjectPosition);
}

