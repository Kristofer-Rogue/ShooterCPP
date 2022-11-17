// ShooterGame. All Rights Reserved.

#include "AI/Services/ShooterChangeWeaponService.h"
#include "AIController.h"
#include "ShooterUtils.h"
#include "Components/ShooterWeaponComponent.h"

UShooterChangeWeaponService::UShooterChangeWeaponService()
{
	NodeName = "Change Weapon";
}

void UShooterChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();

	if (Controller)
	{
		const auto WeaponComponent = ShooterUtils::GetShooterPlayerComponent<UShooterWeaponComponent>(Controller->GetPawn());
		if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
		{
			WeaponComponent->NextWeapon();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}