// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UBoxComponent;

UCLASS()
class HOLYSWORD_API AWeapon : public AActor
{
	GENERATED_BODY()

/*
 * Variables
 */

private:
	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* BoxTraceStart;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* BoxTraceEnd;

/*
 * Functions
 */

private:
	UFUNCTION()
	virtual void ComponentOverlappedHandle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	bool BoxTrace(FHitResult& HitResult);
protected:
	virtual void BeginPlay() override;
	
public:	
	AWeapon();
	virtual void Tick(float DeltaTime) override;
	virtual void SetCollisionEnabled(bool bEnabled);
	
};
