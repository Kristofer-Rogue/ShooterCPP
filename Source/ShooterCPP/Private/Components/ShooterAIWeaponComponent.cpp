// ShooterGame. All Rights Reserved.

#include "Components/ShooterAIWeaponComponent.h"
#include "Weapon/ShooterBaseWeapon.h"

void UShooterAIWeaponComponent::StartFire()
{
	if (!CanFire())
		return;

	if (CurrentWeapon->IsAmmoEmpty())
	{
		NextWeapon();
	}
	else
	{
		CurrentWeapon->StartFire();
	}
}
void UShooterAIWeaponComponent::NextWeapon()
{
	if (!CanEquip())
		return;
	int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	while (NextIndex != CurrentWeaponIndex)
	{
		if (!Weapons[NextIndex]->IsAmmoEmpty())
			break;
		NextIndex = (NextIndex + 1) % Weapons.Num();
	}

	if (CurrentWeaponIndex != NextIndex)
	{
		CurrentWeaponIndex = NextIndex;
		EquipWeapon(CurrentWeaponIndex);
	}
}