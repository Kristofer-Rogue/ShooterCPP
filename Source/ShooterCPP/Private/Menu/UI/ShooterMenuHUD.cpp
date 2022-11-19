// ShooterGame. All Rights Reserved.


#include "Menu/UI/ShooterMenuHUD.h"
#include "Blueprint/UserWidget.h"

void AShooterMenuHUD::BeginPlay()
{
	if (MenuWidgetClass)
	{
		const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
		}
	}
}
