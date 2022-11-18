// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/ShooterBaseWeapon.h"
#include "ShooterLauncherWeapon.generated.h"

class AShooterProjectile;

UCLASS()
class SHOOTERCPP_API AShooterLauncherWeapon : public AShooterBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AShooterProjectile> ProjectileClass;
	virtual void MakeShot() override;
};
