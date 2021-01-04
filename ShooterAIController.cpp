#include "ShooterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"


void AShooterAIController::BeginPlay(){
	Super::BeginPlay();

	if (AIBehavior != nullptr) {
		RunBehaviorTree(AIBehavior);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

void AShooterAIController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

}

bool AShooterAIController::IsDead() const{
	AShooterCharacter* ControllerCharacter = Cast<AShooterCharacter>(GetPawn());
	if (ControllerCharacter != nullptr) {
		return ControllerCharacter->IsDead();
	}
	return true;
}