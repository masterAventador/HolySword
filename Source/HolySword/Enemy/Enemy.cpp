// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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

void AEnemy::PlayAnimMontage(UAnimMontage* AnimMontage, FName SectionName)
{
	if (!AnimMontage) return;
	Super::PlayAnimMontage(AnimMontage,1,SectionName);
}


