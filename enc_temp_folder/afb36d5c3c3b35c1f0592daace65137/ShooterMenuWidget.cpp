// ShooterGame. All Rights Reserved.

#include "Menu/UI/ShooterMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UShooterMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UShooterMenuWidget::OnStartGame);
	}
}

void UShooterMenuWidget::OnStartGame()
{
	const FName StartupLevelName = "StartedLevel";
	UGameplayStatics::OpenLevel(this, StartupLevelName);
}
