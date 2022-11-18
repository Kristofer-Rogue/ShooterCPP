// ShooterGame. All Rights Reserved.

#include "AI/ShooterAICharacter.h"
#include "AI/ShooterAIController.h"
#include "Components/ShooterAIWeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BrainComponent.h"

AShooterAICharacter::AShooterAICharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<UShooterAIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = AShooterAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}

void AShooterAICharacter::OnDeath()
{
	Super::OnDeath();

	const auto ShooterController = Cast<AAIController>(Controller);
	if (ShooterController && ShooterController->BrainComponent)
	{
		ShooterController->BrainComponent->Cleanup();
	}
}
