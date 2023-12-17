// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UInputMappingContext;
struct FInputActionValue;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class HOLYSWORD_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()
	friend class UBaseAnimInstance;

/*
 * Variables
 */

private:
	UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere)
	UInputAction* IALookAction;

	UPROPERTY(EditAnywhere)
	UInputAction* IAMoveAction;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	bool bIsMoving;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	double Velocity;

protected:

public:
	
	

/*
 * Functions
 */
private:
	

protected:
	virtual void BeginPlay() override;

public:
	ABaseCharacter();
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void LookActionFunc(const FInputActionValue& Value);

	virtual void MoveActionFunc(const FInputActionValue& Value);

};
