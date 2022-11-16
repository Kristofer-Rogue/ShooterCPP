#pragma once

class ShooterUtils
{
public:
	template <typename T>
	static T* GetShooterPlayerComponent(AActor* PlayerPawn)
	{
		if (!PlayerPawn)
			return nullptr;

		const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
		return Cast<T>(Component);
	}
};