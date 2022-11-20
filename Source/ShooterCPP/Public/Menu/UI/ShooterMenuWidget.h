// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/ShooterBaseWidget.h"
#include "ShooterCoreTypes.h"
#include "ShooterMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class UShooterGameInstance;
class UShooterLevelItemWidget;

UCLASS()
class SHOOTERCPP_API UShooterMenuWidget : public UShooterBaseWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitGameButton;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* LevelItemsBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> LevelItemWidgetClass;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* HideAnimation;

	virtual void NativeOnInitialized() override;
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation);
	 
private:
	UPROPERTY()
	TArray<UShooterLevelItemWidget*> LevelItemWidgets;

	UFUNCTION()
	void OnStartGame();

	UFUNCTION()
	void OnQuitGame();

	void InitLevelItems();
	void OnLevelSelected(const FLevelData& Data);
	UShooterGameInstance* GetShooterGameInstance() const;
};
