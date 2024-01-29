// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeComponent.h"
#include "HeroEnums.h"

UAttributeComponent::UAttributeComponent():
Health(CharacterDefaultValue::Health),
MaxHealth(CharacterDefaultValue::Health),
Stamina(CharacterDefaultValue::Stamina),
MaxStamina(CharacterDefaultValue::Stamina)
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UAttributeComponent::ReceiveDamage(float Damage)
{
	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);
}

