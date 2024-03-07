// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HolySword/CommonBase/BaseCharacter.h"
#include "HolySword/Interface/GetHitInterface.h"
#include "Enemy.generated.h"

UCLASS()
class HOLYSWORD_API AEnemy : public ABaseCharacter,public IGetHitInterface
{
	GENERATED_BODY()

/*
 * Variables
 */

private:
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* GetHitMontage;

	
/*
 * Functions
 */

	// override functions	
protected:
	virtual void BeginPlay() override;
	
public:
	AEnemy();

	virtual void Tick(float DeltaTime) override;
	

	// custom functions
private:
	
protected:
	
public:

	// override
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void GetHit(AActor* Hitter, const FVector& ImpactPoint,const float Damage) override;
	virtual void PlayGetHitMontage(const FVector& ImpactPoint) override;
};
