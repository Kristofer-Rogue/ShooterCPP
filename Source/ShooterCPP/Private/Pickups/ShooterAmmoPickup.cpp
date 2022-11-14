// ShooterGame. All Rights Reserved.

#include "Pickups/ShooterAmmoPickup.h"
#include "Components/ShooterHealthComponent.h"
#include "Components/ShooterWeaponComponent.h"
#include "ShooterUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool AShooterAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = ShooterUtils::GetShooterPlayerComponent<UShooterHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead())
		return false;	

	const auto WeaponComponent = ShooterUtils::GetShooterPlayerComponent<UShooterWeaponComponent>(PlayerPawn);
	if (!WeaponComponent)
		return false;

	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmmount);
}
 