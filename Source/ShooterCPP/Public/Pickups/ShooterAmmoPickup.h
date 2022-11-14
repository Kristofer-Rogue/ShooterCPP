// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/ShooterBasePickup.h"
#include "ShooterAmmoPickup.generated.h"

class AShooterBaseWeapon;

UCLASS()
class SHOOTERCPP_API AShooterAmmoPickup : public AShooterBasePickup
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
	int32 ClipsAmmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	TSubclassOf<AShooterBaseWeapon> WeaponType;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
