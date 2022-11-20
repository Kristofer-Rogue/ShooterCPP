// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ShooterCoreTypes.h"
#include "ShooterGameHUD.generated.h"

class UShooterBaseWidget;

UCLASS()
class SHOOTERCPP_API AShooterGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<EShooterMatchState, UShooterBaseWidget*> GameWidgets;

	UPROPERTY()
	UShooterBaseWidget* CurrentWidget = nullptr;

	void DrawCrossHair();
	void OnMatchStateChanged(EShooterMatchState State);
};
 