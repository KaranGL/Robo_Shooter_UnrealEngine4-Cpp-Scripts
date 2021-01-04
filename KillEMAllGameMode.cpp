#include "KillEMAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEMAllGameMode::PawnKilled(APawn* PawnKilled) {
	Super::PawnKilled(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());

	if (PlayerController != nullptr) {
		EndGame(false);
	}

	for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld())) {
		if (!Controller->IsDead()) {
			return;
		}
	}
	EndGame(true);
}

void AKillEMAllGameMode::EndGame(bool bISPlayerWinner) {
	for (AController* Controller : TActorRange<AController>(GetWorld())) {
		bool bIsWinner = Controller->IsPlayerController() == bISPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}