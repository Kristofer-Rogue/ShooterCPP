// ShooterGame. All Rights Reserved.

#include "Weapon/ShooterProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/ShooterWeaponVFXComponent.h"

AShooterProjectile::AShooterProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	CollisionComponent->bReturnMaterialOnMove = true;
	SetRootComponent(CollisionComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	MovementComponent->InitialSpeed = 2000.0f;

	WeaponFXComponent = CreateDefaultSubobject<UShooterWeaponVFXComponent>("WeaponFXComponent");
}

void AShooterProjectile::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponFXComponent)
	check(MovementComponent);
	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	CollisionComponent->OnComponentHit.AddDynamic(this, &AShooterProjectile::OnProjectileHit);
	SetLifeSpan(LifeSeconds);
}

void AShooterProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld())
		return;
	MovementComponent->StopMovementImmediately();

	UGameplayStatics::ApplyRadialDamage(GetWorld(), //
		DamageAmount,								//
		GetActorLocation(),							//
		DamageRadius,								//
		UDamageType::StaticClass(),					//
		{},											//
		this,										//
		GetController(),							//
		DoFullDamage);								//

	//DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Emerald, false, 5.0f);
	WeaponFXComponent->PlayImpactFX(Hit);
	Destroy();
}

AController* AShooterProjectile::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}
