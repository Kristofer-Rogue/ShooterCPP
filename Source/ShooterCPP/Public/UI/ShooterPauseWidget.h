// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/ShooterBaseWidget.h"
#include "ShooterPauseWidget.generated.h"

class UButton;

UCLASS()
class SHOOTERCPP_API UShooterPauseWidget : public UShooterBaseWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* ClearPauseButton;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnClearPause();
};
