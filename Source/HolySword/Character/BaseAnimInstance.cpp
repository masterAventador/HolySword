// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimInstance.h"
#include "Hero.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HeroEnums.h"

UBaseAnimInstance::UBaseAnimInstance():
Character(nullptr),
State(CharacterState::Idle),
WeaponState(CharacterWeaponState::Unarmed),
bIsJumping(false)
{
	
}

void UBaseAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	OnMontageEnded.AddDynamic(this,&ThisClass::OnMontageEndHandle);
	Character = Cast<AHero>(TryGetPawnOwner());
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!Character)
	{
		Character = Cast<AHero>(TryGetPawnOwner());
	}
	if (!Character) return;
	
	State = Character->State;
	WeaponState = Character->WeaponState;
	bIsJumping = Character->GetMovementComponent()->IsFalling();
	

	UE_LOG(LogTemp,Warning,TEXT("%d"),State);
	
	GEngine->AddOnScreenDebugMessage(1,-1,FColor::Red,FString::Printf(TEXT("%f"),Character->GetMovementComponent()->Velocity.Z));
	GEngine->AddOnScreenDebugMessage(2,-1,FColor::Orange,FString::Printf(L"isRising = %d",bIsJumping));
}

void UBaseAnimInstance::OnMontageEndHandle(UAnimMontage* Montage, bool bInterrupted)
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

void UBaseAnimInstance::AnimNotify_EnableWeaponCollision(UAnimNotify* Notify)
{
	if (!Character) return;
	Character->SetWeaponCollisionEnabled(true);
	
}

void UBaseAnimInstance::AnimNotify_DisableWeaponCollision(UAnimNotify* Notify)
{
	if (!Character) return;
	Character->SetWeaponCollisionEnabled(false);
}


