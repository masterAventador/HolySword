// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GetHitInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGetHitInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HOLYSWORD_API IGetHitInterface
{
	GENERATED_BODY()

	
public:
	virtual void GetHit(AActor* Hitter,FVector ImpactPoint) = 0;
};
