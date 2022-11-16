// ShooterGame. All Rights Reserved.

#include "Weapon/ShooterRifleWeapon.h"
#include "Weapon/Components/ShooterWeaponVFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

AShooterRifleWeapon::AShooterRifleWeapon()
{
	WeaponFXComponent = CreateDefaultSubobject<UShooterWeaponVFXComponent>("WeaponFXComponent");
}

void AShooterRifleWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponFXComponent);
}

void AShooterRifleWeapon::StartFire()
{
	InitMuzzleFX();
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AShooterRifleWeapon::MakeShot, TimeBetweenShots, true);
	MakeShot();
}

void AShooterRifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
	SetMuzzleFXVisibility(false);
}

void AShooterRifleWeapon::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	FVector TraceFXEnd = TraceEnd;
	if (HitResult.bBlockingHit)
	{
		TraceFXEnd = HitResult.ImpactPoint;
		MakeDamage(HitResult);
		
		WeaponFXComponent->PlayImpactFX(HitResult);
	}
	SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);
	DecreaseAmmo();
}

void AShooterRifleWeapon::InitMuzzleFX()
{
	if (!MuzzleFXComponent)
	{
		MuzzleFXComponent = SpawnMuzzleFX();
	}
	SetMuzzleFXVisibility(true);
}

void AShooterRifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
	const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
	if(TraceFXComponent)
	{
		TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
	}
}

void AShooterRifleWeapon::SetMuzzleFXVisibility(bool Visibility)
{ 
	if (MuzzleFXComponent)
	{
		MuzzleFXComponent->SetPaused(!Visibility);
		MuzzleFXComponent->SetVisibility(Visibility, true);
	}
}

bool AShooterRifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
		return false;

	TraceStart = ViewLocation;
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void AShooterRifleWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto DamagedActor = HitResult.GetActor();
	if (!DamagedActor)
		return;

	DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}