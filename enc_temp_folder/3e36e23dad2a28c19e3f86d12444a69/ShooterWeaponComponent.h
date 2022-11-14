// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShooterCoreTypes.h"
#include "ShooterWeaponComponent.generated.h"

class AShooterBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTERCPP_API UShooterWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UShooterWeaponComponent();

	void StartFire();
	void StopFire();
	void NextWeapon();
	void Reload();

	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	bool TryToAddAmmo(TSubclassOf<AShooterBaseWeapon> WeaponType, int32 ClipsAmmount);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<FWeaponData> WeaponsData;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY()
	AShooterBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<AShooterBaseWeapon*> Weapons;

	UPROPERTY()
	UAnimMontage* CurentReloadAnimMontage = nullptr;

	int32 CurrentWeaponIndex = 0;
	bool EquipAnimInProgress = false; 
	bool ReloadAnimInProgress = false; 

	void SpawnWeapons();
	void AttachWeaponToSocket(AShooterBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	void EquipWeapon(int32 WeaponIndex);
	
	void PlayAnimMontage(UAnimMontage* Animation);
	void InitAnimations();

	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	bool CanFire() const;
	bool CanEquip() const;
	bool CanReload() const;

	void OnEmptyClip();
	void ChangeClip();
};
