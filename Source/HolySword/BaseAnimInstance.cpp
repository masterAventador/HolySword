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
}

void UBaseAnimInstance::AnimNotify_UmarmWeapon(UAnimNotify* Notify)
{
	if (!Character) return;
}

void UBaseAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
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
