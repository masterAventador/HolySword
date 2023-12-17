// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

class ABaseCharacter;
/**
 * 
 */
UCLASS()
class HOLYSWORD_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	/*
	 * Variables
	 */

private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	ABaseCharacter* Character;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	bool bIsMoving;
protected:

public:
	

	/*
	 * Functions
	 */
	
private:
	UBaseAnimInstance();
protected:

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};
