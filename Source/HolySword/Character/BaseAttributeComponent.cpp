// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAttributeComponent.h"
#include "CharacterEnums.h"

UBaseAttributeComponent::UBaseAttributeComponent():
Health(CharacterDefaultValue::Health),
MaxHealth(CharacterDefaultValue::Health),
Stamina(CharacterDefaultValue::Stamina),
MaxStamina(CharacterDefaultValue::Stamina)
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UBaseAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UBaseAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UBaseAttributeComponent::ReceiveDamage(float Damage)
{
	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);
}

bool UBaseAttributeComponent::IsAlive() const
{
	return Health > 0.f;
}

