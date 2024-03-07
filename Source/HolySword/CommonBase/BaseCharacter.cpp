// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "HolySword/Character/AttributeComponent.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>("Attribute");

}

float ABaseCharacter::PlayMontage(UAnimMontage* AnimMontage, FName SectionName)
{
	if (!AnimMontage) return 0;
	return Super::PlayAnimMontage(AnimMontage,1,SectionName);
}

void ABaseCharacter::PlayGetHitMontage(const FVector& ImpactPoint)
{
}

