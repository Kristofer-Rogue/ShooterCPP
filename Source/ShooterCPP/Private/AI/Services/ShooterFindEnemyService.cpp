// ShooterGame. All Rights Reserved.

#include "AI/Services/ShooterFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "ShooterUtils.h"
#include "Components/ShooterAIPerceptionComponent.h"

UShooterFindEnemyService::UShooterFindEnemyService()
{
	NodeName = "Find Name";
}

void UShooterFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = ShooterUtils::GetShooterPlayerComponent<UShooterAIPerceptionComponent>(Controller);
		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
