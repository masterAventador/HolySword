// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

float ABaseCharacter::PlayAnimMontage(UAnimMontage* AnimMontage, FName SectionName)
{
	if (!AnimMontage) return 0;
	return Super::PlayAnimMontage(AnimMontage,1,SectionName);
}

