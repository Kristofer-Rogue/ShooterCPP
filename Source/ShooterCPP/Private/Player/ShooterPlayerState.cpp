// ShooterGame. All Rights Reserved.


#include "Player/ShooterPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerState, All, All);

void AShooterPlayerState::LogInfo()
{
	UE_LOG(LogPlayerState, Display, TEXT("TeamID: %i, Kills: %i, Deaths: %i"), TeamID, KillsNum, DeathsNum);
}
