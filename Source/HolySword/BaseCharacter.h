// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class HOLYSWORD_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

/*
 * Variables
 */

private:
	UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;
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

};
