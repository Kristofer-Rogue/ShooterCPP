// ShooterGame. All Rights Reserved.

#include "Menu/UI/ShooterMenuWidget.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterGameInstance.h"
#include "Menu/UI/ShooterLevelItemWidget.h"
#include "Kismet/KismetSystemLibrary.h"

void UShooterMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UShooterMenuWidget::OnStartGame);
	}
	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &UShooterMenuWidget::OnQuitGame);
	}

	InitLevelItems();
}

void UShooterMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	if (Animation != HideAnimation)
		return;

	const auto ShooterGameInstance = GetShooterGameInstance();
	if (!ShooterGameInstance)
		return;

	UGameplayStatics::OpenLevel(this, ShooterGameInstance->GetStartupLevel().LevelName);
}

void UShooterMenuWidget::OnStartGame()
{
	PlayAnimation(HideAnimation);
}

void UShooterMenuWidget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UShooterMenuWidget::InitLevelItems()
{
	const auto ShooterGameInstance = GetShooterGameInstance();
	if (!ShooterGameInstance)
		return;

	checkf(ShooterGameInstance->GetLevelsData().Num() != 0, TEXT("Levels data must not be empty!"));

	if (!LevelItemsBox)
		return;

	LevelItemsBox->ClearChildren();

	for (auto LevelData : ShooterGameInstance->GetLevelsData())
	{
		const auto LevelItemWidget = CreateWidget<UShooterLevelItemWidget>(GetWorld(), LevelItemWidgetClass);
		if (!LevelItemWidget)
			continue;

		LevelItemWidget->SetLevelData(LevelData);
		LevelItemWidget->OnLevelSelected.AddUObject(this, &UShooterMenuWidget::OnLevelSelected);

		LevelItemsBox->AddChild(LevelItemWidget);
		LevelItemWidgets.Add(LevelItemWidget);
	}

	if (ShooterGameInstance->GetStartupLevel().LevelName.IsNone())
	{
		OnLevelSelected(ShooterGameInstance->GetLevelsData()[0]);
	}
	else
	{
		OnLevelSelected(ShooterGameInstance->GetStartupLevel());
	}
}

void UShooterMenuWidget::OnLevelSelected(const FLevelData& Data)
{
	const auto ShooterGameInstance = GetShooterGameInstance();
	if (!ShooterGameInstance)
		return;

	ShooterGameInstance->SetStartupLevel(Data);

	for (auto LevelItemWidget : LevelItemWidgets)
	{
		if (LevelItemWidget)
		{
			const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
			LevelItemWidget->SetSelected(IsSelected);
		}
	}
}

UShooterGameInstance* UShooterMenuWidget::GetShooterGameInstance() const
{
	if (!GetWorld())
		return nullptr;

	return GetWorld()->GetGameInstance<UShooterGameInstance>();
}
