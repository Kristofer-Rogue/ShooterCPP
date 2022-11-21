// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "ShooterGameUserSettings.generated.h"

class UShooterGameSetting;

DECLARE_MULTICAST_DELEGATE(FOnSettingsUpdatedSignature);

UCLASS()
class SHOOTERCPP_API UShooterGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	UShooterGameUserSettings();
	static UShooterGameUserSettings* Get();

	const TArray<UShooterGameSetting*>& GetVideoSettings() const;

	void RunBenchmark();

	FOnSettingsUpdatedSignature OnVideoSettingsUpdated;

private:
	UPROPERTY()
	TArray<UShooterGameSetting*> VideoSettings;
};
