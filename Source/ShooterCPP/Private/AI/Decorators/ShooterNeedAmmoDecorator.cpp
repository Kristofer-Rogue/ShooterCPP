// ShooterGame. All Rights Reserved.

#include "AI/Decorators/ShooterNeedAmmoDecorator.h"
#include "AIController.h"
#include "ShooterUtils.h"
#include "Components/ShooterWeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogNeedAmmo, All, All);

UShooterNeedAmmoDecorator::UShooterNeedAmmoDecorator()
{
	NodeName = "Need Ammo";
}

bool UShooterNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller)
		return false;

	const auto WeaponComponent = ShooterUtils::GetShooterPlayerComponent<UShooterWeaponComponent>(Controller->GetPawn());
	if (!WeaponComponent)
		return false;

	//UE_LOG(LogNeedAmmo, Display, TEXT("%s"), WeaponComponent->NeedAmmo(WeaponType) ? "true" : "false");
	return WeaponComponent->NeedAmmo(WeaponType);
}