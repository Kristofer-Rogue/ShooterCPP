// ShooterGame. All Rights Reserved.

#include "Player/ShooterPlayerController.h"
#include "Components/ShooterRespawnComponent.h"

AShooterPlayerController::AShooterPlayerController()
{
	ShooterRespawnComponent = CreateDefaultSubobject<UShooterRespawnComponent>("ShooterRespawnComponent");
}
