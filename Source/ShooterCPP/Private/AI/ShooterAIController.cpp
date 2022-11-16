// ShooterGame. All Rights Reserved.


#include "AI/ShooterAIController.h"
#include "AI/ShooterAICharacter.h"
#include "Components/ShooterAIPerceptionComponent.h"

AShooterAIController::AShooterAIController()
{
	ShooterAIPerceptionComponent = CreateDefaultSubobject<UShooterAIPerceptionComponent>("ShooterPerceptionComponent");
	SetPerceptionComponent(*ShooterAIPerceptionComponent);
}

void AShooterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto ShooterCharacter = Cast<AShooterAICharacter>(InPawn);
	if (ShooterCharacter)
	{
		RunBehaviorTree(ShooterCharacter->BehaviorTreeAsset);
	}

}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto AimActor = ShooterAIPerceptionComponent->GetClosestEnemy();
	SetFocus(AimActor);
}
