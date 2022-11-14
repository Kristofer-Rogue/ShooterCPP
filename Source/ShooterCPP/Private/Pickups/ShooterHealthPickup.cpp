// ShooterGame. All Rights Reserved.

#include "Pickups/ShooterHealthPickup.h"
#include "Components/ShooterHealthComponent.h"
#include "ShooterUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool AShooterHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = ShooterUtils::GetShooterPlayerComponent<UShooterHealthComponent>(PlayerPawn);
	if (!HealthComponent)
		return false;

	return HealthComponent->TryToAddHealth(HealthAmmount);
}