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
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float RotationRate = 10.f;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;
	
	UPROPERTY(VisibleAnywhere)
	float Health;
public:	
	// Sets default values for this character's properties
	AShooterCharacter();

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Shoot();

	UPROPERTY(VisibleAnywhere)
	int Ammo;

	UPROPERTY(VisibleAnywhere)
	int ClipSize;

	UPROPERTY(VisibleAnywhere)
	int SpareAmmo;

	UFUNCTION(BlueprintPure)
	int GetAmmoValue() const;

	UFUNCTION(BlueprintPure)
	int GetClipValue() const;

	void Reload();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
};