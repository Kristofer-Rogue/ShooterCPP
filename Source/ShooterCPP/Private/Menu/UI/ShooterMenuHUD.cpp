// ShooterGame. All Rights Reserved.


#include "Menu/UI/ShooterMenuHUD.h"
#include "UI/ShooterBaseWidget.h"

void AShooterMenuHUD::BeginPlay()
{
	if (MenuWidgetClass)
	{
		const auto MenuWidget = CreateWidget<UShooterBaseWidget>(GetWorld(), MenuWidgetClass);
		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
			MenuWidget->Show();
		}
	}
}
