// ShooterGame. All Rights Reserved.

#include "Menu/UI/ShooterMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterGameInstance.h"

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
	if (!GetWorld())
		return;

	const auto ShooterGameInstance = GetWorld()->GetGameInstance<UShooterGameInstance>();
	if (!ShooterGameInstance)
		return;

	if (ShooterGameInstance->GetStartupLevelName().IsNone())
		return; 

	UGameplayStatics::OpenLevel(this, ShooterGameInstance->GetStartupLevelName());
}
