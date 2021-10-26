// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionObject.h"
#include "Components/PointLightComponent.h"
#include "InteractableLight.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECTGDS6_API AInteractableLight : public AInteractionObject
{
	GENERATED_BODY()
	
public:
	AInteractableLight();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Interact();

	UPROPERTY()
		bool state;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float intensity;

	UPROPERTY(EditAnywhere)
		UPointLightComponent* Light;
};
