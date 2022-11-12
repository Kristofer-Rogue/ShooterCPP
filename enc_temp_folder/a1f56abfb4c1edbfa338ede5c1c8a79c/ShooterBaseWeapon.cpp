// ShooterGame. All Rights Reserved.

#include "Weapon/ShooterBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

AShooterBaseWeapon::AShooterBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void AShooterBaseWeapon::Fire()
{
	UE_LOG(LogBaseWeapon, Display, TEXT("Fire!"));
}

void AShooterBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}
