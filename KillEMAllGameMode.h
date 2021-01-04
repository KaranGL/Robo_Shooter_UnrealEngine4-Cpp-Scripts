#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterGameModeBase.h"
#include "KillEMAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AKillEMAllGameMode : public ASimpleShooterGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* PawnKilled) override;

private:
	void EndGame(bool bIsPlayerWinner);
};
