// ShooterGame. All Rights Reserved.

#include "Weapon/ShooterRifleWeapon.h"
#include "Weapon/Components/ShooterWeaponVFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/Controller.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogRifleWeapon, All, All);

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
	InitFX();
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AShooterRifleWeapon::MakeShot, TimeBetweenShots, true);
	MakeShot();
}

void AShooterRifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
	SetFXActive(false);
}

void AShooterRifleWeapon::MakeShot()
{
	if (!GetWorld())
	{
		StopFire();
		return;
	}
	if (IsAmmoEmpty())
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), NoAmmoSound, GetActorLocation());
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

void AShooterRifleWeapon::InitFX()
{
	if (!MuzzleFXComponent)
	{
		MuzzleFXComponent = SpawnMuzzleFX();
	}

	if (!FireAudioComponent)
	{
		FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
	}
	SetFXActive(true);
}

void AShooterRifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
	const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
	if(TraceFXComponent)
	{
		TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
	}
}

void AShooterRifleWeapon::SetFXActive(bool IsActive)
{ 
	if (MuzzleFXComponent)
	{
		MuzzleFXComponent->SetPaused(!IsActive);
		MuzzleFXComponent->SetVisibility(IsActive, true);
	}

	if (FireAudioComponent)
	{
		IsActive ? FireAudioComponent->Play() : FireAudioComponent->Stop();
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

void AShooterRifleWeapon::Zoom(bool Enabled)
{
	const auto Controller = Cast<APlayerController>(GetController());
	if (!Controller || !Controller->PlayerCameraManager)
		return;

	if (Enabled)
	{
		DefaultCameraFOV = Controller->PlayerCameraManager->GetFOVAngle();
	}

	Controller->PlayerCameraManager->SetFOV(Enabled ? FOVZoomAngle : DefaultCameraFOV);
}

void AShooterRifleWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto DamagedActor = HitResult.GetActor();
	if (!DamagedActor)
		return;

	FPointDamageEvent PointDamageEvent;
	PointDamageEvent.HitInfo = HitResult;
	DamagedActor->TakeDamage(DamageAmount, PointDamageEvent, GetController(), this);
}

AController* AShooterRifleWeapon::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}