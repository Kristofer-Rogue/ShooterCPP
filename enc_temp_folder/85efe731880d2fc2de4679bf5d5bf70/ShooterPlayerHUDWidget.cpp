// ShooterGame. All Rights Reserved.

#include "Player/ShooterPlayerHUDWidget.h"
#include "Components/ShooterHealthComponent.h"
#include "Components/ShooterWeaponComponent.h"

float UShooterPlayerHUDWidget::GetHealthPercent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player)
		return 0.0f;
	const auto Component = Player->GetComponentByClass(UShooterHealthComponent::StaticClass());
	const auto HealthComponent = Cast<UShooterHealthComponent>(Component);
	if (!HealthComponent)
		return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool UShooterPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = GetWeaponComponent();
	if (!WeaponComponent)
		return false;

	return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool UShooterPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = GetWeaponComponent();
	if (!WeaponComponent)
		return false;

	return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}

UShooterWeaponComponent* UShooterPlayerHUDWidget::GetWeaponComponent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player)
		return nullptr;
	const auto Component = Player->GetComponentByClass(UShooterWeaponComponent::StaticClass());
	const auto WeaponComponent = Cast<UShooterWeaponComponent>(Component);
	return WeaponComponent;
}
