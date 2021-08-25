// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectInteraction.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UObjectInteraction::UObjectInteraction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectInteraction::BeginPlay()
{
	Super::BeginPlay();

	if (!TriggerArea)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the trigger event move component on it, but has no trigger volume assigned"), *GetOwner()->GetName());
	}

	TriggerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UObjectInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TriggerArea && TriggerArea->IsOverlappingActor(TriggerActor))
	{
		
	}
}

