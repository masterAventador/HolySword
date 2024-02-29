// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseController.h"

ABaseController::ABaseController()
{
	SetShowMouseCursor(true);
}

void ABaseController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI{});
}
