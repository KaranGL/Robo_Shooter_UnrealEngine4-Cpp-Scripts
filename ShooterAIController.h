#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"


UCLASS()
class SIMPLESHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	bool IsDead() const;
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere)
	float SightRadius = 200;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;
};
