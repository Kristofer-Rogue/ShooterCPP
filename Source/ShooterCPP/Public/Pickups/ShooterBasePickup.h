// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShooterBasePickup.generated.h"

class USphereComponent;

UCLASS()
class SHOOTERCPP_API AShooterBasePickup : public AActor
{
	GENERATED_BODY()

public:
	AShooterBasePickup();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent* CollisionComponent;

	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
	virtual void Tick(float DeltaTime) override;
};
