// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "ShooterHealthPercentDecorator.generated.h"

UCLASS()
class SHOOTERCPP_API UShooterHealthPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	UShooterHealthPercentDecorator();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float HealthPercent = 0.6f;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
