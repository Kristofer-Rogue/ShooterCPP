// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ShooterWeaponComponent.h"
#include "ShooterAIWeaponComponent.generated.h"

UCLASS()
class SHOOTERCPP_API UShooterAIWeaponComponent : public UShooterWeaponComponent
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void NextWeapon() override;
};
