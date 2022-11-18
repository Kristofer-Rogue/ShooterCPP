// ShooterGame. All Rights Reserved.

#include "Player/ShooterPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Components/ShooterWeaponComponent.h"

AShooterPlayerCharacter::AShooterPlayerCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit)
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void AShooterPlayerCharacter::OnDeath()
{
	Super::OnDeath();
	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

void AShooterPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	check(WeaponComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AShooterPlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &AShooterPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AShooterPlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AShooterPlayerCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AShooterPlayerCharacter::OnStopRunning);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UShooterWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UShooterWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UShooterWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UShooterWeaponComponent::Reload);
}
void AShooterPlayerCharacter::MoveForward(float Amount)
{
	IsMovingForward = Amount > 0.0f;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AShooterPlayerCharacter::MoveRight(float Amount)
{
	if (Amount == 0.0f)
		return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void AShooterPlayerCharacter::OnStartRunning()
{
	WantsToRun = true;
}

void AShooterPlayerCharacter::OnStopRunning()
{
	WantsToRun = false;
}
bool AShooterPlayerCharacter::IsRunning() const
{
	return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}