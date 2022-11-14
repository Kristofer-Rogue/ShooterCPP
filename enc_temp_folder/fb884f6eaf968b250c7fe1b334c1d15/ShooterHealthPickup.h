// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/ShooterAmmoPickup.h"
#include "ShooterHealthPickup.generated.h"

UCLASS()
class SHOOTERCPP_API AShooterHealthPickup : public AShooterAmmoPickup
{
	GENERATED_BODY()

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
