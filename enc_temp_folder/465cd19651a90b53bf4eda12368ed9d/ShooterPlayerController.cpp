// ShooterGame. All Rights Reserved.

#include "Player/ShooterPlayerController.h"
#include "Components/ShooterRespawnComponent.h"
#include "ShooterGameModeBase.h"

AShooterPlayerController::AShooterPlayerController()
{
	ShooterRespawnComponent = CreateDefaultSubobject<UShooterRespawnComponent>("ShooterRespawnComponent");
}

void AShooterPlayerController::BeginPlay()
{
	if (GetWorld())
	{
		const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &AShooterPlayerController::OnMatchStateChanged);
		}
	}
}

void AShooterPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (!InputComponent)
		return;

	InputComponent->BindAction("PauseGame", IE_Pressed, this, &AShooterPlayerController::OnPauseGame);
}

void AShooterPlayerController::OnPauseGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode())
		return;

	GetWorld()->GetAuthGameMode()->SetPause(this);
}

void AShooterPlayerController::OnMatchStateChanged(EShooterMatchState State)
{
	if (State == EShooterMatchState::InProgress)
	{
		bShowMouseCursor = false;
	}
	else
	{
		bShowMouseCursor = true;
	}
}
