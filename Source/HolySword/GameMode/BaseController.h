// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BaseController.generated.h"

/**
 * 
 */
UCLASS()
class HOLYSWORD_API ABaseController : public APlayerController
{
	GENERATED_BODY()
public:
	ABaseController();

	void BeginPlay() override;
};
