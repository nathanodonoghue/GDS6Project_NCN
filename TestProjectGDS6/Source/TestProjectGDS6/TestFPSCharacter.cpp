// Fill out your copyright notice in the Description page of Project Settings.


#include "TestFPSCharacter.h"
#include "Gauntlet.h"
#include "InteractionObject.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "TestProjectGDS6GameModeBase.h"

// Sets default values
ATestFPSCharacter::ATestFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	Gauntlet = GetWorld()->SpawnActor<AGauntlet>(WeaponClass);

	Gauntlet->SetOwner(this);
}

bool ATestFPSCharacter::IsDead() const
{
	return Health <= 0;
}

float ATestFPSCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

// Called every frame
void ATestFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATestFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ATestFPSCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &ATestFPSCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &ATestFPSCharacter::LookRightRate);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &ATestFPSCharacter::Attack);
	PlayerInputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed, this, &ATestFPSCharacter::Interact);
}

float ATestFPSCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);

	if (IsDead()) 
	{
		ATestProjectGDS6GameModeBase* GameMode = GetWorld()->GetAuthGameMode<ATestProjectGDS6GameModeBase>();

		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}

void ATestFPSCharacter::MoveForward(float AxisValue) 
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void ATestFPSCharacter::MoveRight(float AxisValue) 
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void ATestFPSCharacter::LookUpRate(float AxisValue) 
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void ATestFPSCharacter::LookRightRate(float AxisValue) 
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void ATestFPSCharacter::Attack()
{
	Gauntlet->PullTrigger();
}

void ATestFPSCharacter::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Interaction button pressed"));

	FHitResult OutHit;
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	if (GetWorld()->LineTraceSingleByChannel(OutHit, PlayerViewPointLocation, LineTraceEnd, ECC_Visibility))
	{
		AInteractionObject* Obj = Cast<AInteractionObject>(OutHit.Actor);
		if (Obj)
		{
			Obj->InteractWith();
		}
	}
}

