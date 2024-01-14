// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimInstance.h"

#include "BaseCharacter.h"
#include "CharacterEnums.h"

UBaseAnimInstance::UBaseAnimInstance():
Character(nullptr),
CharacterState(CharacterState::Idle),
CharacterWeaponState(CharacterWeaponState::Unarmed)
{
	
}

void UBaseAnimInstance::AnimNotify_ArmWeapon(UAnimNotify* Notify)
{
	if (!Character) return;
	Character->ArmWeapon();
}

void UBaseAnimInstance::AnimNotify_UnarmWeapon(UAnimNotify* Notify)
{
	if (!Character) return;
	Character->UmarmWeapon();
}

void UBaseAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	OnMontageEnded.AddDynamic(this,&ThisClass::OnMontageEndHandle);
	Character = Cast<ABaseCharacter>(TryGetPawnOwner());
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!Character)
	{
		Character = Cast<ABaseCharacter>(TryGetPawnOwner());
	}
	if (!Character) return;
	CharacterState = Character->State;
	CharacterWeaponState = Character->WeaponState;

	UE_LOG(LogTemp,Warning,TEXT("%d"),CharacterState);
	
	GEngine->AddOnScreenDebugMessage(1,-1,FColor::Red,FString::Printf(TEXT("%d"),CharacterState));
}

void UBaseAnimInstance::OnMontageEndHandle(UAnimMontage* Montage, bool bInterrupted)
{
	
}
