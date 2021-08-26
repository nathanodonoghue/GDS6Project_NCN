// Fill out your copyright notice in the Description page of Project Settings.


#include "Gauntlet.h"

#include "Components/SkeletalMeshComponent.h"

// Sets default values
AGauntlet::AGauntlet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGauntlet::PullTrigger()
{
	UE_LOG(LogTemp, Warning, TEXT("You've been shot!"));
}

// Called when the game starts or when spawned
void AGauntlet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGauntlet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
