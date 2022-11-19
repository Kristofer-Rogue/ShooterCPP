// ShooterGame. All Rights Reserved.

#include "UI/ShooterPlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UShooterPlayerStatRowWidget::SetPlayerName(const FText& Text)
{
	if (!PlayerNameTextBlock)
		return;

	PlayerNameTextBlock->SetText(Text);

}

void UShooterPlayerStatRowWidget::SetKills(const FText& Text)
{
	if (!KillsTextBlock)
		return;

	KillsTextBlock->SetText(Text);
}

void UShooterPlayerStatRowWidget::SetDeaths(const FText& Text)
{
	if (!DeathTextBlock)
		return;

	DeathTextBlock->SetText(Text);
}

void UShooterPlayerStatRowWidget::SetTeam(const FText& Text)
{
	if (!TeamTextBlock)
		return;

	TeamTextBlock->SetText(Text);
}

void UShooterPlayerStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
	if (!PlayerIndicatorImage)
		return;

	PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

