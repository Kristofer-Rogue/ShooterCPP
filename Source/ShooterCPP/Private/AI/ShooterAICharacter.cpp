// ShooterGame. All Rights Reserved.

#include "AI/ShooterAICharacter.h"
#include "AI/ShooterAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

AShooterAICharacter::AShooterAICharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AShooterAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}
