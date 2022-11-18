// ShooterGame. All Rights Reserved.

#include "Components/ShooterRespawnComponent.h"
#include "ShooterGameModeBase.h"

UShooterRespawnComponent::UShooterRespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UShooterRespawnComponent::Respawn(int32 RespawnTime)
{
	if (!GetWorld())
		return;

	RespawnCountDown = RespawnTime;
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &UShooterRespawnComponent::RespawnTimerUpdate, 1.0f, true);
}

bool UShooterRespawnComponent::IsRespawnInProgress() const
{
	return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}

void UShooterRespawnComponent::RespawnTimerUpdate()
{
	if (--RespawnCountDown == 0)
	{
		if (!GetWorld())
			return;

		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

		const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
		if (!GameMode)
			return;

		GameMode->RespawnRequest(Cast<AController>(GetOwner()));
	}
}
