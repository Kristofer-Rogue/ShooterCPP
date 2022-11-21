// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShooterVideoSettingsWidget.generated.h"

class UVerticalBox;
class UShooterSettingOptionWidget;
class UButton;

UCLASS()
class SHOOTERCPP_API UShooterVideoSettingsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VideoSettingsContainer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UShooterSettingOptionWidget> SettingOptionWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UButton* RunBenchmarkButton;

	virtual void NativeOnInitialized() override;

	private:
	UFUNCTION()
	void OnBenchmark();

	void OnVideoSettingsUpdated();
};