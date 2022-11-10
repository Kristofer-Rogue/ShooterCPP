// ShooterGame. All Rights Reserved.


#include "Components/ShooterCharacterMovementComp.h"
#include "Player/ShooterBaseCharacter.h"

float UShooterCharacterMovementComp::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const AShooterBaseCharacter* Player = Cast<AShooterBaseCharacter>(GetPawnOwner());
	return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
