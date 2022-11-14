// ShooterGame. All Rights Reserved.

#include "Pickups/ShooterBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

AShooterBasePickup::AShooterBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);
}

void AShooterBasePickup::BeginPlay()
{
	Super::BeginPlay();
}

void AShooterBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	UE_LOG(LogBasePickup, Display, TEXT("Pickup was taken"));
	Destroy();
}

void AShooterBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
