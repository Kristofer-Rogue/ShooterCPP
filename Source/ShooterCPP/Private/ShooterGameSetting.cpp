// ShooterGame. All Rights Reserved.


#include "ShooterGameSetting.h"

void UShooterGameSetting::SetName(const FString& InName)
{
	Name = InName;
}

void UShooterGameSetting::SetOptions(const TArray<FSettingOption>& InOptions)
{
	Options = InOptions;
}

FSettingOption UShooterGameSetting::GetCurrentOption() const
{
	const int32 CurrentValue = GetCurrentValue();
	const auto Option = Options.FindByPredicate([&](const auto& Opt) { return CurrentValue == Opt.Value; });

	if (!Option)
	{
		return FSettingOption{};
	}
	return *Option;
}

FString UShooterGameSetting::GetName() const
{
	return Name;
}

void UShooterGameSetting::AddGetter(TFunction<int32()> Func)
{
	Getter = Func;
}

void UShooterGameSetting::AddSetter(TFunction<void(int32)> Func)
{
	Setter = Func;
}

void UShooterGameSetting::ApplyNextOption()
{
	const int32 CurrentIndex = GetCurrentIndex();
	if (CurrentIndex == INDEX_NONE)
		return;

	const int32 NextIndex = (CurrentIndex + 1) % Options.Num();
	SetCurrentValue(Options[NextIndex].Value);
}

void UShooterGameSetting::ApplyPrevOption()
{
	const int32 CurrentIndex = GetCurrentIndex();
	if (CurrentIndex == INDEX_NONE)
		return;

	const int32 PrevIndex = CurrentIndex == 0 ? Options.Num() - 1 : CurrentIndex - 1;
	SetCurrentValue(Options[PrevIndex].Value);
}

int32 UShooterGameSetting::GetCurrentValue() const
{
	if (!Getter)
	{
		return INDEX_NONE;
	}
	return Getter();
}

void UShooterGameSetting::SetCurrentValue(int32 Value)
{
	if (!Setter)
	{
		return;
	}
	Setter(Value);
}

int32 UShooterGameSetting::GetCurrentIndex() const
{
	const int32 CurrentValue = GetCurrentValue();
	return Options.IndexOfByPredicate([&](const auto& Opt) { return CurrentValue == Opt.Value; });
}
