// ShooterGame. All Rights Reserved.

#include "Components/ShooterWeaponComponent.h"
#include "Weapon/ShooterBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/ShooterEquipFinishAnimNotify.h"
#include "Animations/ShooterReloadFinishedAnimNotify.h"
#include "Animations/AnimUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

constexpr static int32 WeaponNum = 2;

UShooterWeaponComponent::UShooterWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UShooterWeaponComponent::StartFire()
{
	if (!CanFire())
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

	checkf(WeaponsData.Num() == WeaponNum, TEXT("Our character can hold only %i weapons"), WeaponNum);

	InitAnimations();
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
}

void UShooterWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();
	Super::EndPlay(EndPlayReason);
}

void UShooterWeaponComponent::SpawnWeapons()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!GetWorld() || !Character)
		return;

	for (auto WeaponData : WeaponsData)
	{
		auto Weapon = GetWorld()->SpawnActor<AShooterBaseWeapon>(WeaponData.WeaponClass);
		if (!Weapon)
			continue;
		Weapon->OnClipEmpty.AddUObject(this, &UShooterWeaponComponent::OnEmptyClip);
		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);
		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}
}

void UShooterWeaponComponent::AttachWeaponToSocket(AShooterBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
	if (!Weapon || !SceneComponent)
		return;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UShooterWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
	{
		return;
	}
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
		return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	const auto CurrentWeaponData = WeaponsData.FindByPredicate([&](const FWeaponData& Data) { // Find the animation for CurrentWeapon in the array of structures
		return Data.WeaponClass == CurrentWeapon->GetClass();								  //
	});
	CurentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
	EquipAnimInProgress = true;
	PlayAnimMontage(EquipAnimMontage);
}

void UShooterWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
		return;
	Character->PlayAnimMontage(Animation);
}

void UShooterWeaponComponent::InitAnimations()
{
	auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<UShooterEquipFinishAnimNotify>(EquipAnimMontage);
	if (EquipFinishedNotify)
	{
		EquipFinishedNotify->OnNotified.AddUObject(this, &UShooterWeaponComponent::OnEquipFinished);
	}
	else
	{
		UE_LOG(LogWeaponComponent, Error, TEXT("Equip anim notify is forgotten to set"));
		checkNoEntry();
	}

	for (auto WeaponData : WeaponsData)
	{
		auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<UShooterReloadFinishedAnimNotify>(WeaponData.ReloadAnimMontage);
		if (!ReloadFinishedNotify)
		{
			UE_LOG(LogWeaponComponent, Error, TEXT("Reload anim notify is forgotten to set"));
			checkNoEntry();
		}
		ReloadFinishedNotify->OnNotified.AddUObject(this, &UShooterWeaponComponent::OnReloadFinished);
	}
}

bool UShooterWeaponComponent::CanFire() const
{
	return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool UShooterWeaponComponent::CanEquip() const
{
	return !EquipAnimInProgress && !ReloadAnimInProgress;
}

void UShooterWeaponComponent::OnEmptyClip()
{
	ChangeClip();
}

void UShooterWeaponComponent::ChangeClip()
{
	if (!CanReload())
		return;
	CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();
	ReloadAnimInProgress = true;
	PlayAnimMontage(CurentReloadAnimMontage);
}

bool UShooterWeaponComponent::CanReload() const
{
	return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress && CurrentWeapon->CanReload();
}

void UShooterWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || MeshComponent != Character->GetMesh())
		return;

	EquipAnimInProgress = false;
}

void UShooterWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || MeshComponent != Character->GetMesh())
		return;

	ReloadAnimInProgress = false;
}

void UShooterWeaponComponent::NextWeapon()
{
	if (CanEquip())
	{
		CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
		EquipWeapon(CurrentWeaponIndex);
	}
}

void UShooterWeaponComponent::Reload()
{
	ChangeClip();
}
