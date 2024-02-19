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

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AEnemy::GetHit(AActor* Hitter, FVector ImpactPoint)
{
	DrawDebugSphere(GetWorld(),ImpactPoint,10,10,FColor::Red,false,2);
	DrawDebugLine(GetWorld(),GetActorLocation(),GetActorLocation() + GetActorForwardVector()*100,FColor::Purple,true);

	FVector ImpactPointLower = FVector(ImpactPoint.X,ImpactPoint.Y,GetActorLocation().Z);
	FVector HitVector = (ImpactPointLower - GetActorLocation()).GetSafeNormal();
	double CosTheta = FVector::DotProduct(GetActorForwardVector(),HitVector);
	double ArcCosTheta = FMath::Acos(CosTheta);
	double ThetaWithDegree = FMath::RadiansToDegrees(ArcCosTheta);
	UE_LOG(LogTemp,Warning,L"ThetaWithDegree == %f",ThetaWithDegree);
}

