// ShooterGame. All Rights Reserved.

#include "AI/Services/ShooterFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "ShooterUtils.h"
#include "Components/ShooterWeaponComponent.h"

UShooterFireService::UShooterFireService()
{
	NodeName = "Fire";
}

void UShooterFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if (Controller)
	{
		const auto WeaponComponent = ShooterUtils::GetShooterPlayerComponent<UShooterWeaponComponent>(Controller->GetPawn());
		if (WeaponComponent)
		{
			HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
