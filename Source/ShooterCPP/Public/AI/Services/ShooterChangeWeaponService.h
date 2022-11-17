// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ShooterChangeWeaponService.generated.h"

UCLASS()
class SHOOTERCPP_API UShooterChangeWeaponService : public UBTService
{
	GENERATED_BODY()

public:
	UShooterChangeWeaponService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float Probability = 0.5;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};