// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

enum class CharacterWeaponState : uint8;
enum class CharacterState : uint8;
class AHero;
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
	AHero* Character;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	CharacterState State;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	CharacterWeaponState WeaponState;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	bool bIsJumping;

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

protected:
	UFUNCTION()
	virtual void OnMontageEndHandle(UAnimMontage* Montage, bool bInterrupted);
	
	UFUNCTION()
	virtual void AnimNotify_ArmWeapon(UAnimNotify* Notify);

	UFUNCTION()
	virtual void AnimNotify_UnarmWeapon(UAnimNotify* Notify);

	UFUNCTION()
	virtual void AnimNotify_EnableWeaponCollision(UAnimNotify* Notify);

	UFUNCTION()
	virtual void AnimNotify_DisableWeaponCollision(UAnimNotify* Notify);

};
