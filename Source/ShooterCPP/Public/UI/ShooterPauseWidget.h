// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShooterPauseWidget.generated.h"

class UButton;

UCLASS()
class SHOOTERCPP_API UShooterPauseWidget : public UUserWidget
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
