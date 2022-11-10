// ShooterGame. All Rights Reserved.


#include "Player/ShooterBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"

AShooterBaseCharacter::AShooterBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void AShooterBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShooterBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShooterBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AShooterBaseCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnAround", this, &AShooterBaseCharacter::TurnAround);
}

void AShooterBaseCharacter::MoveForward(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AShooterBaseCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void AShooterBaseCharacter::LookUp(float Amount)
{
	AddControllerPitchInput(Amount);
}

void AShooterBaseCharacter::TurnAround(float Amount)
{
	AddControllerYawInput(Amount);
}

