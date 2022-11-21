// ShooterGame. All Rights Reserved.

#include "Components/ShooterHealthComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "ShooterGameModeBase.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Perception/AISense_Damage.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

UShooterHealthComponent::UShooterHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UShooterHealthComponent::TryToAddHealth(float HealthAmount)
{
	if (IsDead() || IsHealthFull())
		return false;

	SetHealth(Health + MaxHealth);
	return true;
}

bool UShooterHealthComponent::IsHealthFull() const
{
	return FMath::IsNearlyEqual(Health, MaxHealth);
}

void UShooterHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth > 0);

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UShooterHealthComponent::OnTakeAnyDamage);
		ComponentOwner->OnTakePointDamage.AddDynamic(this, &UShooterHealthComponent::OnTakePointDamage);
		ComponentOwner->OnTakeRadialDamage.AddDynamic(this, &UShooterHealthComponent::OnTakeRadialDamage);
	}
}

void UShooterHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
}

void UShooterHealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	const auto FinalDamage = Damage * GetPointDamageModifier(DamagedActor, BoneName);
	ApplyDamage(FinalDamage, InstigatedBy);
}

void UShooterHealthComponent::OnTakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin, FHitResult HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
	ApplyDamage(Damage, InstigatedBy);
}

void UShooterHealthComponent::HealUpdate()
{
	SetHealth(Health + HealModifier);

	if (IsHealthFull() && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void UShooterHealthComponent::SetHealth(float NewHealth)
{
	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - Health;
	Health = NextHealth;
	OnHealthChanged.Broadcast(Health, HealthDelta);
}

void UShooterHealthComponent::PlayCameraShake()
{
	if (IsDead())
		return;

	const auto Player = Cast<APawn>(GetOwner());
	if (!Player)
		return;
	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager)
		return;

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

void UShooterHealthComponent::Killed(AController* KillerController)
{
	if (!GetWorld())
		return;

	const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode)
		return;

	const auto Player = Cast<APawn>(GetOwner());
	const auto VictimController = Player ? Player->Controller : nullptr;

	GameMode->Killed(KillerController, VictimController);
}

void UShooterHealthComponent::ApplyDamage(float Damage, AController* InstigatedBy)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld())
		return;

	SetHealth(Health - Damage);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

	if (IsDead())
	{
		Killed(InstigatedBy);
		OnDeath.Broadcast();
	}
	else if (AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UShooterHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
	}

	PlayCameraShake();
	ReportDamageEvent(Damage, InstigatedBy);
}

float UShooterHealthComponent::GetPointDamageModifier(AActor* DamagedActor, const FName& BoneName)
{
	const auto Character = Cast<ACharacter>(DamagedActor);
	if (!Character || !Character->GetMesh() || !Character->GetMesh()->GetBodyInstance(BoneName))
		return 1.0f;

	const auto PhysicalMaterial = Character->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();
	if (!PhysicalMaterial || !DamageModifiers.Contains(PhysicalMaterial))
		return 1.0f;

	return DamageModifiers[PhysicalMaterial];
}

void UShooterHealthComponent::ReportDamageEvent(float Damage, AController* InstigatedBy)
{
	if (!InstigatedBy || !InstigatedBy->GetPawn() || !GetOwner())
		return;

	UAISense_Damage::ReportDamageEvent(GetWorld(),	 //
		GetOwner(), InstigatedBy->GetPawn(),		 //
		Damage,										 //
		InstigatedBy->GetPawn()->GetActorLocation(), //
		GetOwner()->GetActorLocation());
}
