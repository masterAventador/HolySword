// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "Components/CapsuleComponent.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}


