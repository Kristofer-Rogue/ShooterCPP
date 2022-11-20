// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ShooterSoundtFunctionLibrary.generated.h"

class USoundClass;

UCLASS()
class SHOOTERCPP_API UShooterSoundtFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void SetSoundClassVolume(USoundClass* SoundClass, float Volume);

	UFUNCTION(BlueprintCallable)
	static void ToggleSoundClassVolume(USoundClass* SoundClass);
};
