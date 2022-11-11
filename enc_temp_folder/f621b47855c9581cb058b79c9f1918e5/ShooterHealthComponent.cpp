// ShooterGame. All Rights Reserved.

#include "Components/ShooterHealthComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

UShooterHealthComponent::UShooterHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UShooterHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UShooterHealthComponent::OnTakeAnyDamage);
	}
}

void UShooterHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	if (Damage <= 0.0f || IsDead() || GetWorld())
		return;

	SetHealth(Health - Damage);
	UE_LOG(LogHealthComponent, Display, TEXT("Now health is %f"), Health);
	

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if (AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UShooterHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
	}
}

void UShooterHealthComponent::HealUpdate()
{
	SetHealth(Health + HealModifier);

	if (FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	} 
}

void UShooterHealthComponent::SetHealth(float NewHealth)
{
	UE_LOG(LogHealthComponent, Display, TEXT("Now health is %f"), NewHealth);
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}
