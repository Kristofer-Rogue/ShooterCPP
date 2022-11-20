// ShooterGame. All Rights Reserved.

#include "AI/ShooterAICharacter.h"
#include "AI/ShooterAIController.h"
#include "Components/ShooterAIWeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BrainComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/ShooterHealthBarWidget.h"
#include "Components/ShooterHealthComponent.h"

AShooterAICharacter::AShooterAICharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<UShooterAIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = AShooterAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
	HealthWidgetComponent->SetupAttachment(GetRootComponent());
	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void AShooterAICharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthWidgetComponent);
	FTimerHandle HealthBarVisibilityTimer;
	GetWorldTimerManager().SetTimer(HealthBarVisibilityTimer, this,&AShooterAICharacter::UpdateHealthWidgetVisibility, HealthBarVisibilityUpdateTime, true);
}

void AShooterAICharacter::OnDeath()
{
	Super::OnDeath();

	const auto ShooterController = Cast<AAIController>(Controller);
	if (ShooterController && ShooterController->BrainComponent)
	{
		ShooterController->BrainComponent->Cleanup();
	}
}

void AShooterAICharacter::OnHealthChanged(float Health, float HealthDelta)
{
	Super::OnHealthChanged(Health, HealthDelta);

	const auto HealthBarWidget = Cast<UShooterHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
	if (!HealthBarWidget)
		return;

	HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
}

void AShooterAICharacter::UpdateHealthWidgetVisibility()
{
	if (!GetWorld() || !GetWorld()->GetFirstPlayerController() || !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator())
		return;

	const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
	const auto Distance = FVector::Distance(PlayerLocation, GetActorLocation());
	HealthWidgetComponent->SetVisibility(Distance < HealthVisibilityDistance, true);
}
