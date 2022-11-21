// ShooterGame. All Rights Reserved.

#include "UI/ShooterSettingOptionWidget.h"
#include "ShooterGameSetting.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UShooterSettingOptionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	NextSettingButton->OnClicked.AddDynamic(this, &UShooterSettingOptionWidget::OnNextSetting);
	PrevSettingButton->OnClicked.AddDynamic(this, &UShooterSettingOptionWidget::OnPrevSetting);
}

void UShooterSettingOptionWidget::Init(UShooterGameSetting* InSetting)
{
	Setting = MakeWeakObjectPtr(InSetting);
	check(Setting.IsValid());

	UpdateTexts();
}

void UShooterSettingOptionWidget::UpdateTexts()
{
	if (Setting.IsValid())
	{
		SettingDisplayName->SetText(FText::FromString(Setting->GetName()));
		SettingCurrentValue->SetText(FText::FromString(Setting->GetCurrentOption().Name));
	}
}

void UShooterSettingOptionWidget::OnNextSetting()
{
	if (Setting.IsValid())
	{
		Setting->ApplyNextOption();
		SettingCurrentValue->SetText(FText::FromString(Setting->GetCurrentOption().Name));
	}
}

void UShooterSettingOptionWidget::OnPrevSetting()
{
	if (Setting.IsValid())
	{
		Setting->ApplyPrevOption();
		SettingCurrentValue->SetText(FText::FromString(Setting->GetCurrentOption().Name));
	}
}
