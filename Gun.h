// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

private:
	UPROPERTY(VisibleAnywhere)	
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1500;

	UPROPERTY(EditAnywhere)
	float Damage = 10;

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);

	AController* GetOwnerController() const;
};