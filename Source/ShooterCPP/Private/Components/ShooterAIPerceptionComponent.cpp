// ShooterGame. All Rights Reserved.

#include "Components/ShooterAIPerceptionComponent.h"
#include "AIController.h"
#include "ShooterUtils.h"
#include "Components/ShooterHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* UShooterAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	if (PercieveActors.Num() == 0)
		return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller)
		return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn)
		return nullptr;

	float ClosestDistance = MAX_FLT;
	AActor* ClosestPawn = nullptr;
	for (const auto PercieveActor : PercieveActors)
	{
		const auto HealthComponent = ShooterUtils::GetShooterPlayerComponent<UShooterHealthComponent>(PercieveActor);
		if (HealthComponent && !HealthComponent->IsDead())
		{
			const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < ClosestDistance)
			{
				ClosestDistance = CurrentDistance;
				ClosestPawn = PercieveActor;
			}
		}
	}
	return ClosestPawn;
}
