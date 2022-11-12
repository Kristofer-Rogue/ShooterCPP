// ShooterGame. All Rights Reserved.

#include "Components/ShooterWeaponComponent.h"
#include "Weapon/ShooterBaseWeapon.h"
#include "GameFramework/Character.h"

UShooterWeaponComponent::UShooterWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UShooterWeaponComponent::Fire()
{
	if (!CurrentWeapon)
		return;
	CurrentWeapon->Fire();
}

void UShooterWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

void UShooterWeaponComponent::SpawnWeapon()
{
	if (!GetWorld())
		return;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
		return;

	CurrentWeapon = GetWorld()->SpawnActor<AShooterBaseWeapon>(WeaponClass);
	if (!CurrentWeapon)
		return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
}