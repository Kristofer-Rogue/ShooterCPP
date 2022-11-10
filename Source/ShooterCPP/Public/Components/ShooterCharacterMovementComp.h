// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ShooterCharacterMovementComp.generated.h"

UCLASS()
class SHOOTERCPP_API UShooterCharacterMovementComp : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "1.1", ClampMax = "10.0"))
	float RunModifier = 2.0f;
	virtual float GetMaxSpeed() const override;
};
 