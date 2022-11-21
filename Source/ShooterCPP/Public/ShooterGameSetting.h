// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShooterGameSetting.generated.h"

USTRUCT()
struct FSettingOption
{
	GENERATED_BODY()

	FString Name;

	int32 Value;
};

UCLASS()
class UShooterGameSetting : public UObject
{
	GENERATED_BODY()

public:
	void SetName(const FString& InName);
	void SetOptions(const TArray<FSettingOption>& InOptions);

	FSettingOption GetCurrentOption() const;
	FString GetName() const;
	void AddGetter(TFunction<int32()> Func);
	void AddSetter(TFunction<void(int32)> Func);

	void ApplyNextOption();
	void ApplyPrevOption();

private:
	FString Name;
	TArray<FSettingOption> Options;
	TFunction<int32()> Getter;
	TFunction<void(int32)> Setter;

	int32 GetCurrentValue() const;
	void SetCurrentValue(int32 Value);
	int32 GetCurrentIndex() const;
};
