// ShooterGame. All Rights Reserved.

#include "Pickups/ShooterHealthPickup.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool AShooterHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	UE_LOG(LogHealthPickup, Display, TEXT("Health was taken!"));
	return true;
}
