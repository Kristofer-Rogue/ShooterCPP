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

public:
	virtual bool Initialize() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* ClearPauseButton;

private:
	UFUNCTION()
	void OnClearPause();
};
