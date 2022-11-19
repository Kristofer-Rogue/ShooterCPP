// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterCoreTypes.h"
#include "ShooterPlayerController.generated.h"

class UShooterRespawnComponent;

UCLASS()
class SHOOTERCPP_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AShooterPlayerController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	UShooterRespawnComponent* ShooterRespawnComponent;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void OnPauseGame();
	void OnMatchStateChanged(EShooterMatchState State);
};
