// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShooterWeaponComponent.generated.h"

class AShooterBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTERCPP_API UShooterWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UShooterWeaponComponent();

	void Fire();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AShooterBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponAttachPointName = "WeaponSocket";

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	AShooterBaseWeapon* CurrentWeapon = nullptr;

	void SpawnWeapon();
};
