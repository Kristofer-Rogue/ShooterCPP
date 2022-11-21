// ShooterGame. All Rights Reserved.


#include "UI/ShooterVideoSettingsWidget.h"
#include "ShooterGameUserSettings.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "UI/ShooterSettingOptionWidget.h"

void UShooterVideoSettingsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	auto* UserSettings = UShooterGameUserSettings::Get();
	if (!UserSettings)
	{
		return;
	}

	UserSettings->LoadSettings();

	const auto VideoSettings = UserSettings->GetVideoSettings();

	check(VideoSettingsContainer);
	VideoSettingsContainer->ClearChildren();

	for (auto* Setting : VideoSettings)
	{
		const auto SettingWidget = CreateWidget<UShooterSettingOptionWidget>(this, SettingOptionWidgetClass);
		check(SettingWidget);
		SettingWidget->Init(Setting);
		VideoSettingsContainer->AddChild(SettingWidget);
	}

	RunBenchmarkButton->OnClicked.AddDynamic(this, &UShooterVideoSettingsWidget::OnBenchmark);

	UserSettings->OnVideoSettingsUpdated.AddUObject(this, &UShooterVideoSettingsWidget::OnVideoSettingsUpdated);
}

void UShooterVideoSettingsWidget::OnBenchmark()
{
	if (auto* UserSettings = UShooterGameUserSettings::Get())
	{
		UserSettings->RunBenchmark();
	}
}

void UShooterVideoSettingsWidget::OnVideoSettingsUpdated()
{
	if (!VideoSettingsContainer)
		return;

	for (auto* Widget : VideoSettingsContainer->GetAllChildren())
	{
		if (auto* SettingOptionWidget = Cast<UShooterSettingOptionWidget>(Widget))
		{
			SettingOptionWidget->UpdateTexts();
		}
	}
}
 