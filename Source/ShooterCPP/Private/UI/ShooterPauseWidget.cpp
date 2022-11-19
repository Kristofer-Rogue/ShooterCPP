// ShooterGame. All Rights Reserved.

#include "UI/ShooterPauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

void UShooterPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &UShooterPauseWidget::OnClearPause);
	}
}

void UShooterPauseWidget::OnClearPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode())
		return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}
