// ShooterGame. All Rights Reserved.

#include "UI/ShooterSpectatorWidget.h"
#include "ShooterUtils.h"
#include "Components/ShooterRespawnComponent.h"

bool UShooterSpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
	const auto RespawnComponent = ShooterUtils::GetShooterPlayerComponent<UShooterRespawnComponent>(GetOwningPlayer());
	if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress())
		return false;

	CountDownTime = RespawnComponent->GetRespawnCountDown();
	return true;
} 