// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ShooterNextLocationTask.generated.h"

UCLASS()
class SHOOTERCPP_API UShooterNextLocationTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UShooterNextLocationTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float Radius = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector AimLocationKey;
};
