// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseAttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOLYSWORD_API UBaseAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,Category=ActorAttribute)
	float Health;

	UPROPERTY(EditAnywhere,Category=ActorAttribtue)
	float MaxHealth;

	UPROPERTY(EditAnywhere,Category=ActorAttribute)
	float Stamina;

	UPROPERTY(EditAnywhere,Category=ActorAttribute)
	float MaxStamina;
	

protected:
	virtual void BeginPlay() override;
	
public:	
	UBaseAttributeComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE float GetHealthPercent() const { return Health/MaxHealth; }
	FORCEINLINE float GetStaminaPercent() const { return Stamina/MaxStamina; }

	void ReceiveDamage(float Damage);
	bool IsAlive() const;


};
