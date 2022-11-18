// ShooterGame. All Rights Reserved.


#include "UI/ShooterGameDataWidget.h"
#include "Player/ShooterPlayerState.h"
#include "ShooterGameModeBase.h"

int32 UShooterGameDataWidget::GetKillsNum() const
{
	const auto PlayerState = GetShooterPlayerState();
	return PlayerState ? PlayerState->GetKillsNum() : 0;
}

int32 UShooterGameDataWidget::GetDeathsNum() const
{
	const auto PlayerState = GetShooterPlayerState();
	return PlayerState ? PlayerState->GetDeathsNum() : 0;
}

int32 UShooterGameDataWidget::GetCurrentRoundNum() const
{
	const auto GameMode = GetShooterGameMode();
	return GameMode ? GameMode->GetCurrentRoundNum() : 0;
}

int32 UShooterGameDataWidget::GetTotalRoundsNum() const
{
	const auto GameMode = GetShooterGameMode();
	return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 UShooterGameDataWidget::GetRoundSecondsRemaining() const
{
	const auto GameMode = GetShooterGameMode();
	return GameMode ? GameMode->GetRoundSecondsRemaining() : 0;
}

AShooterGameModeBase* UShooterGameDataWidget::GetShooterGameMode() const
{
	return GetWorld() ? Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

AShooterPlayerState* UShooterGameDataWidget::GetShooterPlayerState() const
{
	return GetOwningPlayer() ? Cast<AShooterPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
