#include "ShooterCharacter.h"
#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"


// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpareAmmo = 300;
	Ammo = 10;
	ClipSize = 20;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
}

bool AShooterCharacter::IsDead() const {
	return Health <= 0;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("MoveSideWays"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookSideWays"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookSideRate"), this, &AShooterCharacter::LookRightRate);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Reload);
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) {
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Shot!!Remaining health is %f"), Health);
	
	if (IsDead()) {
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (GameMode != nullptr) {
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}

void AShooterCharacter::MoveForward(float AxisValue) {
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue) {
	AddMovementInput(GetActorRightVector() * AxisValue);
} 

void AShooterCharacter::LookUpRate(float AxisValue) {
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(float AxisValue) {
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Shoot() {
	if (Ammo == 0) {
		return;
	}
	Gun->PullTrigger();
	Ammo--;
}

float AShooterCharacter::GetHealthPercent() const{
	return Health / MaxHealth;
}

void AShooterCharacter::Reload() {
	if (SpareAmmo <= 0) {
		return;
	}
	else {
		if (SpareAmmo > ClipSize) {
			if (Ammo == 0) {
				Ammo = ClipSize;
				SpareAmmo -= ClipSize;
			}
			else if (Ammo > 0 && Ammo < ClipSize) {
				int BulletsTaken = ClipSize - Ammo;
				Ammo = ClipSize;
				SpareAmmo -= BulletsTaken;
			}
			else if (Ammo == ClipSize) {
				return;
			}
		}
		else if (SpareAmmo == ClipSize) {
			if (Ammo == 0) {
				Ammo = ClipSize;
				SpareAmmo = 0;
			}
			else if (Ammo > 0 && Ammo < ClipSize) {
				int BulletsTaken = ClipSize - Ammo;
				Ammo = ClipSize;
				SpareAmmo -= BulletsTaken;
			}
			else if (Ammo == ClipSize) {
				return;
			}
		}
		else {
			if (Ammo == 0) {
				Ammo = SpareAmmo;
				SpareAmmo = 0;
			}
			else if (Ammo > 0 && Ammo < ClipSize) {
				int bulletsTaken = ClipSize - Ammo;
				Ammo = ClipSize;
				SpareAmmo -= bulletsTaken;
			}
			else if (Ammo == ClipSize) {
				return;
			}
		}
	}
}

int AShooterCharacter::GetAmmoValue() const {
	return Ammo;
}

int AShooterCharacter::GetClipValue() const {
	return SpareAmmo;
}