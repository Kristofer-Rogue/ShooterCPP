// ShooterGame. All Rights Reserved.

#include "Weapon/ShooterBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

AShooterBaseWeapon::AShooterBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void AShooterBaseWeapon::StartFire()
{
}

void AShooterBaseWeapon::StopFire()
{
}

void AShooterBaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMesh);
	checkf(DefaultAmmo.Bullets > 0, TEXT("Bullets count could't be less or equal zero"));
	checkf(DefaultAmmo.Clips > 0, TEXT("Clips count could't be less or equal zero"));
	CurrentAmmo = DefaultAmmo;
}

void AShooterBaseWeapon::MakeShot()
{
}

APlayerController* AShooterBaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player)
		return nullptr;

	return Player->GetController<APlayerController>();
}

bool AShooterBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto ShooterCharacter = Cast<ACharacter>(GetOwner());
	if (!ShooterCharacter)
		return false;

	if (ShooterCharacter->IsPlayerControlled())
	{
		const auto Controller = GetPlayerController();
		if (!Controller)
			return false;

		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}
	else
	{
		ViewLocation = GetMuzzleWorldLocation();
		ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
	}

	return true;
}

FVector AShooterBaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool AShooterBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
		return false;

	TraceStart = ViewLocation;
	const FVector ShootDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void AShooterBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if (!GetWorld())
		return;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	CollisionParams.bReturnPhysicalMaterial = true;

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

void AShooterBaseWeapon::DecreaseAmmo()
{
	
	if (IsClipEmpty())
	{
		UE_LOG(LogBaseWeapon, Warning, TEXT("in if"));
		StopFire();
		if (CurrentAmmo.Infinite || CurrentAmmo.Clips > 0)
			OnClipEmpty.Broadcast();
	}
	CurrentAmmo.Bullets--;
	LogAmmo();
} 

bool AShooterBaseWeapon::IsAmmoEmpty() const
{
	return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool AShooterBaseWeapon::IsClipEmpty() const
{
	return CurrentAmmo.Bullets == 0;
}

bool AShooterBaseWeapon::IsAmmoFull() const
{
	return CurrentAmmo.Clips == DefaultAmmo.Clips && 
		CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

bool AShooterBaseWeapon::NeedAmmo() const
{
	return CurrentAmmo.Clips < DefaultAmmo.Clips;
}

void AShooterBaseWeapon::ChangeClip()
{
	if (!CurrentAmmo.Infinite)
	{
		if (CurrentAmmo.Clips == 0)
		{
			UE_LOG(LogBaseWeapon, Warning, TEXT("No more clips"));
			return;
		}
		CurrentAmmo.Clips--;
	}
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	UE_LOG(LogBaseWeapon, Display, TEXT("Change Clip"));
}

bool AShooterBaseWeapon::CanReload() const
{
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}

bool AShooterBaseWeapon::TryToAddAmmo(int32 ClipsAmount)
{
	UE_LOG(LogBaseWeapon, Display, TEXT("here"));
	if (CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount <= 0)
		return false;

	if (IsAmmoEmpty())
	{
		CurrentAmmo.Clips = FMath::Clamp(ClipsAmount, 0, DefaultAmmo.Clips + 1);
		OnClipEmpty.Broadcast();
	}
	else if (CurrentAmmo.Clips < DefaultAmmo.Clips)
	{
		CurrentAmmo.Clips = FMath::Clamp(CurrentAmmo.Clips + ClipsAmount, 0, DefaultAmmo.Clips);
	}
	else
	{
		return false;
	}

	return true;
}

void AShooterBaseWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
	AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
	UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfo);
}

UNiagaraComponent* AShooterBaseWeapon::SpawnMuzzleFX()
{
	return UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX, //
		WeaponMesh,												  //
		MuzzleSocketName,										  //
		FVector::ZeroVector,									  //
		FRotator::ZeroRotator,									  //
		EAttachLocation::SnapToTarget,							  //
		true);
}
