// ShooterGame. All Rights Reserved.


#include "UI/ShooterHealthBarWidget.h"
#include "Components/ProgressBar.h"

void UShooterHealthBarWidget::SetHealthPercent(float Percent)
{
	if (!HealthProgressBar)
		return;

	const auto HealthBarVisibility = (Percent > PercentVisibilityTreshold || FMath::IsNearlyZero(Percent) //
			? ESlateVisibility::Hidden
			: ESlateVisibility::Visible);

	HealthProgressBar->SetVisibility(HealthBarVisibility);

	const auto HealthBarColor = Percent > PercentColodThreshold ? GoodColor : BadColor;

	HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);

	HealthProgressBar->SetPercent(Percent);
}