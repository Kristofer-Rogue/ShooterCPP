// ShooterGame. All Rights Reserved.

#include "Pickups/ShooterBasePickup.h"
#include "Components/SphereComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

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
	GenerateRotationYaw();
	check(CollisionComponent);
}

void AShooterBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);
	if (GivePickupTo(Pawn))
	{
		PickupWasTaken();
	}
}

void AShooterBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));
	AddActorLocalOffset({ 0, 0, AmplitudeZ * FMath::Sin(FrequencyZ * GetWorld()->GetTimeSeconds()) });
}

bool AShooterBasePickup::CouldBeTaken() const
{
	return !GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
}

bool AShooterBasePickup::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

void AShooterBasePickup::PickupWasTaken()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false, true);
	}
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AShooterBasePickup::Respawn, RespawnTime);

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupTakenSound, GetActorLocation());
}

void AShooterBasePickup::Respawn()
{
	GenerateRotationYaw();
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
	}
}

void AShooterBasePickup::GenerateRotationYaw()
{
	const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
	RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}
