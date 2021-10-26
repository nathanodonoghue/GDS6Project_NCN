// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableLight.h"

AInteractableLight::AInteractableLight()
{
	state = true;
	intensity = 100000.f;
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	Light->SetupAttachment(GetRootComponent());
}

void AInteractableLight::BeginPlay()
{
	Super::BeginPlay();
	Light->SetIntensity(intensity);
}

void AInteractableLight::Interact()
{
	if (state)
	{
		Light->SetIntensity(0);
	}
	else
	{
		Light->SetIntensity(intensity);
	}
	state = !state;
}
