// ShooterGame. All Rights Reserved.

#include "Components/ShooterHealthComponent.h"

// Sets default values for this component's properties
UShooterHealthComponent::UShooterHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UShooterHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}
