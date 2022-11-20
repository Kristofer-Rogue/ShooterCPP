// ShooterGame. All Rights Reserved.


#include "Sound/ShooterSoundtFunctionLibrary.h"
#include "Sound/SoundClass.h"

void UShooterSoundtFunctionLibrary::SetSoundClassVolume(USoundClass* SoundClass, float Volume)
{
	if (!SoundClass)
		return;

	SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.0f, 1.0f);
}

void UShooterSoundtFunctionLibrary::ToggleSoundClassVolume(USoundClass* SoundClass)
{
	if (!SoundClass)
		return;

	const auto NextVolume = SoundClass->Properties.Volume > 0.0f ? 0.0f : SoundClass->Properties.Volume;
	SetSoundClassVolume(SoundClass, NextVolume);
}
