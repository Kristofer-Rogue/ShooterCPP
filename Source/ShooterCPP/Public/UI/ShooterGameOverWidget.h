// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShooterCoreTypes.h"
#include "ShooterGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class SHOOTERCPP_API UShooterGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerStatBox;

	UPROPERTY(meta = (BindWidget))
	UButton* ResetLevelButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

	virtual void NativeOnInitialized() override;

private:
	void OnMatchStateChanged(EShooterMatchState State);
	void UpdatePlayersStat();

	UFUNCTION()
	void OnResetLevel();
};
