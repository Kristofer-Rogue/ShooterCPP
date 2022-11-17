// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/ShooterBaseCharacter.h"
#include "ShooterAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class SHOOTERCPP_API AShooterAICharacter : public AShooterBaseCharacter
{
	GENERATED_BODY()

public:
	AShooterAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;
};
