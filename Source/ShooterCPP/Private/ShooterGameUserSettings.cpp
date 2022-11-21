// ShooterGame. All Rights Reserved.

#include "ShooterGameUserSettings.h"
#include "ShooterGameSetting.h"

UShooterGameUserSettings::UShooterGameUserSettings()
{
	const TArray<FSettingOption> VFXOptions = { { "Low", 0 }, { "Medium", 1 }, { "High", 2 }, { "Epic", 3 } };
	{
		auto* Setting = NewObject<UShooterGameSetting>();
		Setting->SetName("Anti-Aliasing");
		Setting->SetOptions(VFXOptions);
		Setting->AddGetter([&]() { return GetAntiAliasingQuality(); });
		Setting->AddSetter([&](int Level) { SetAntiAliasingQuality(Level); ApplySettings(false); });
		VideoSettings.Add(Setting);
	}
	{
		auto* Setting = NewObject<UShooterGameSetting>();
		Setting->SetName("Textures");
		Setting->SetOptions(VFXOptions);
		Setting->AddGetter([&]() { return GetTextureQuality(); });
		Setting->AddSetter([&](int Level) { SetTextureQuality (Level); ApplySettings(false); });
		VideoSettings.Add(Setting);
	}
	{
		auto* Setting = NewObject<UShooterGameSetting>();
		Setting->SetName("Global Illumination");
		Setting->SetOptions(VFXOptions);
		Setting->AddGetter([&]() { return GetGlobalIlluminationQuality(); });
		Setting->AddSetter([&](int Level) { SetGlobalIlluminationQuality(Level); ApplySettings(false); });
		VideoSettings.Add(Setting);
	}
	{
		auto* Setting = NewObject<UShooterGameSetting>();
		Setting->SetName("Shadows");
		Setting->SetOptions(VFXOptions);
		Setting->AddGetter([&]() { return GetShadowQuality(); });
		Setting->AddSetter([&](int Level) { SetShadowQuality(Level); ApplySettings(false); });
		VideoSettings.Add(Setting);
	}
	{
		auto* Setting = NewObject<UShooterGameSetting>();
		Setting->SetName("PostProcessing");
		Setting->SetOptions(VFXOptions);
		Setting->AddGetter([&]() { return GetPostProcessingQuality(); });
		Setting->AddSetter([&](int Level) { SetPostProcessingQuality(Level); ApplySettings(false); });
		VideoSettings.Add(Setting);
	}
}

UShooterGameUserSettings* UShooterGameUserSettings::Get()
{
	return GEngine ? Cast<UShooterGameUserSettings>(GEngine->GetGameUserSettings()) : nullptr;
}

const TArray<UShooterGameSetting*>& UShooterGameUserSettings::GetVideoSettings() const
{
	return VideoSettings;
}

void UShooterGameUserSettings::RunBenchmark()
{
	RunHardwareBenchmark();
	ApplySettings(false);
	OnVideoSettingsUpdated.Broadcast();
}
