// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ShooterFindEnemyService.generated.h"

UCLASS()
class SHOOTERCPP_API UShooterFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
	UShooterFindEnemyService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
