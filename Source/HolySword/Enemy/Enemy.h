// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class HOLYSWORD_API AEnemy : public ACharacter
{
	GENERATED_BODY()

/*
 * Variables
 */

private:
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* GetHitMontage;

	
/*
 * Functions
 */

	// override functions	
protected:
	virtual void BeginPlay() override;
	
public:
	AEnemy();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;


	// custom functions

private:

protected:
	virtual void PlayAnimMontage(UAnimMontage* AnimMontage,FName SectionName);
	
public:
	
	
};
