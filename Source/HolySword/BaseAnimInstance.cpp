// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimInstance.h"

#include "BaseCharacter.h"

UBaseAnimInstance::UBaseAnimInstance():bIsMoving(false),Character(nullptr)
{
	
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

	bIsMoving = Character->bIsMoving;
}
