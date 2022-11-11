// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShooterBaseWeapon.generated.h"

UCLASS()
class SHOOTERCPP_API AShooterBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	AShooterBaseWeapon();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	virtual void BeginPlay() override;
};
