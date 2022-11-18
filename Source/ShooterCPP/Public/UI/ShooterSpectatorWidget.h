// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShooterSpectatorWidget.generated.h"

UCLASS()
class SHOOTERCPP_API UShooterSpectatorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetRespawnTime(int32& CountDownTime) const;
};
