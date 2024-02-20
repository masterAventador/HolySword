// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "Components/CapsuleComponent.h"
#include "HolySword/Character/Enums.h"


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
	FVector ImpactPointLower = FVector(ImpactPoint.X,ImpactPoint.Y,GetActorLocation().Z);
	FVector HitVector = (ImpactPointLower - GetActorLocation()).GetSafeNormal();
	double CosTheta = FVector::DotProduct(GetActorForwardVector(),HitVector);
	double ArcCosTheta = FMath::Acos(CosTheta);
	double DegreeOfTheta = FMath::RadiansToDegrees(ArcCosTheta);

	FVector CrossResultVector = GetActorForwardVector().Cross(HitVector);
	if (CrossResultVector.Z < 0)
	{
		DegreeOfTheta *= -1;
	}

	FName GetHitSection = MontageSectionName::GetHit_B;
	
	if (DegreeOfTheta > -45.f && DegreeOfTheta < 45.f)
	{
		GetHitSection = MontageSectionName::GetHit_F;
	} else if (DegreeOfTheta < -45.f && DegreeOfTheta > -135.f)
	{
		GetHitSection = MontageSectionName::GetHit_L;
	} else if (DegreeOfTheta > 45.f && DegreeOfTheta < 135.f)
	{
		GetHitSection = MontageSectionName::GetHit_R;
	}
	PlayMontage(GetHitMontage,GetHitSection);
}

