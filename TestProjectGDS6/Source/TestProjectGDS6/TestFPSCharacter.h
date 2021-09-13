// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestFPSCharacter.generated.h"

class AGauntlet;

UCLASS()
class TESTPROJECTGDS6_API ATestFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintPure)
		bool IsDead() const;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	void Attack();

	UPROPERTY(EditAnywhere)
		float RotationRate = 100;
	UPROPERTY(EditDefaultsOnly)
		float MaxHealth = 100;
	UPROPERTY(VisibleAnywhere)
		float Health;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AGauntlet> WeaponClass;

	UPROPERTY()
		AGauntlet* Gauntlet;
};
