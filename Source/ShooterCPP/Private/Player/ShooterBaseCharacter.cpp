// ShooterGame. All Rights Reserved.


#include "Player/ShooterBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ShooterCharacterMovementComp.h"

AShooterBaseCharacter::AShooterBaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<UShooterCharacterMovementComp>(ACharacter::CharacterMovementComponentName))
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
	PlayerInputComponent->BindAxis("LookUp", this, &AShooterBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &AShooterBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed,this, &AShooterBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AShooterBaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AShooterBaseCharacter::OnStopRunning);
}

bool AShooterBaseCharacter::IsRunning() const
{
	return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

float AShooterBaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero()) return 0.0f;
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void AShooterBaseCharacter::MoveForward(float Amount)
{
	IsMovingForward = Amount > 0.0f;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AShooterBaseCharacter::MoveRight(float Amount)
{
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void AShooterBaseCharacter::OnStartRunning()
{
	WantsToRun = true;
}

void AShooterBaseCharacter::OnStopRunning()
{
	WantsToRun = false;
}
