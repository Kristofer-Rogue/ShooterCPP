// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ShooterCoreTypes.h"
#include "ShooterGameInstance.generated.h"

UCLASS()
class SHOOTERCPP_API UShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FLevelData GetStartupLevel() const { return StartupLevel; }
	FLevelData SetStartupLevel(const FLevelData& Data) { return StartupLevel = Data; }

	TArray<FLevelData> GetLevelsData() const { return LevelsData; }
	FName GetMenuLevelName() const { return MenuLevelName; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TArray<FLevelData> LevelsData;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName MenuLevelName = NAME_None;

private:
	FLevelData StartupLevel;
};
