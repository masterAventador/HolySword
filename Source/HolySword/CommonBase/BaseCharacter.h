// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UAttributeComponent;

UCLASS()
class HOLYSWORD_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	UAttributeComponent* AttributeComponent;

public:
	ABaseCharacter();

	virtual float PlayMontage(UAnimMontage* AnimMontage, FName SectionName);
	virtual void PlayGetHitMontage(const FVector& ImpactPoint);
};
