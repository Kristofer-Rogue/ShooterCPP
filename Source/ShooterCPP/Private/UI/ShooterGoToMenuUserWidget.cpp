// ShooterGame. All Rights Reserved.


#include "UI/ShooterGoToMenuUserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterGameInstance.h"

void UShooterGoToMenuUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GoToMenuButton)
	{
		GoToMenuButton->OnClicked.AddDynamic(this, &UShooterGoToMenuUserWidget::OnGoToMenu);
	}
}

void UShooterGoToMenuUserWidget::OnGoToMenu()
{
	if (!GetWorld())
		return;

	const auto ShooterGameInstance = GetWorld()->GetGameInstance<UShooterGameInstance>();
	if (!ShooterGameInstance)
		return;

	if (ShooterGameInstance->GetMenuLevelName().IsNone())
		return;

	UGameplayStatics::OpenLevel(this, ShooterGameInstance->GetMenuLevelName());
}