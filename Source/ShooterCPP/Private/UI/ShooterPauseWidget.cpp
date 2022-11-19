// ShooterGame. All Rights Reserved.

#include "UI/ShooterPauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

bool UShooterPauseWidget::Initialize()
{
	const auto InitStatus = Super::Initialize();

	if (ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &UShooterPauseWidget::OnClearPause);
	}

	return InitStatus;
}

void UShooterPauseWidget::OnClearPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode())
		return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}
