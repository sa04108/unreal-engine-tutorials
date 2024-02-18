// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext *InputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	class UInputAction *MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	UInputAction *LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	UInputAction *JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	UInputAction *WalkAction;

	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	UInputAction *ShootAction;

	bool bWalking = false;

	void Move(const struct FInputActionValue &Value);
	void Look(const FInputActionValue &Value);
	void Walk() { bWalking = true; }
	void StopWalking() { bWalking = false; }

public:
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void Shoot();

private:
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun *Gun;
};
