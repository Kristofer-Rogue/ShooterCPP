// ShooterGame. All Rights Reserved.

#include "Components/ShooterWeaponComponent.h"
#include "Weapon/ShooterBaseWeapon.h"
#include "GameFramework/Character.h"

UShooterWeaponComponent::UShooterWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UShooterWeaponComponent::StartFire()
{
	if (!CurrentWeapon)
		return;
	CurrentWeapon->StartFire();
}

void UShooterWeaponComponent::StopFire()
{
	if (!CurrentWeapon)
		return;
	CurrentWeapon->StopFire();
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
	CurrentWeapon->SetOwner(Character);
}