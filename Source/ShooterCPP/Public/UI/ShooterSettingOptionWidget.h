// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShooterSettingOptionWidget.generated.h"

class UTextBlock;
class UShooterGameSetting;
class UButton;

UCLASS()
class SHOOTERCPP_API UShooterSettingOptionWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SettingDisplayName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SettingCurrentValue;

	UPROPERTY(meta = (BindWidget))
	UButton* NextSettingButton;

	UPROPERTY(meta = (BindWidget))
	UButton* PrevSettingButton;

	virtual void NativeOnInitialized() override;

	private:
	TWeakObjectPtr<UShooterGameSetting> Setting;

	void Init(UShooterGameSetting* InSetting);
	void UpdateTexts();

	UFUNCTION()
	void OnNextSetting();

	UFUNCTION()
	void OnPrevSetting();

	friend class UShooterVideoSettingsWidget;
};
