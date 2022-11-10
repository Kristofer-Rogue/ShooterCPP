// ShooterGame. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SHOOTERCPP_API AShooterBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterBaseCharacter(const FObjectInitializer& ObjInit);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsRunning() const;
	
private:
	bool WantsToRun = false;
	bool IsMovingForward = false;

	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void OnStartRunning();
	void OnStopRunning();
};
