// ShooterGame. All Rights Reserved.


#include "Menu/ShooterMenuPlayerController.h"
#include "ShooterGameInstance.h"

void AShooterMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}
