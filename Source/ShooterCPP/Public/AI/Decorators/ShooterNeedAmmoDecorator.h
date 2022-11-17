// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "ShooterNeedAmmoDecorator.generated.h"

class AShooterBaseWeapon;

UCLASS()
class SHOOTERCPP_API UShooterNeedAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	UShooterNeedAmmoDecorator();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TSubclassOf<AShooterBaseWeapon> WeaponType;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
