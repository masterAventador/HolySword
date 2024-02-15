// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Components/BoxComponent.h"
#include "HolySword/Interface/GetHitInterface.h"
#include "Kismet/KismetSystemLibrary.h"


AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(MeshComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("CollisionBox");
	BoxComponent->SetupAttachment(GetRootComponent());
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	BoxTraceStart = CreateDefaultSubobject<USceneComponent>("BoxTraceStart");
	BoxTraceStart->SetupAttachment(GetRootComponent());

	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>("BoxTraceEnd");
	BoxTraceEnd->SetupAttachment(GetRootComponent());
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::ComponentOverlappedHandle);
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::SetCollisionEnabled(bool bEnabled)
{
	BoxComponent->SetCollisionEnabled(bEnabled ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
}

void AWeapon::ComponentOverlappedHandle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                        const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Warning,L"-----------Starting----------");
	if (OtherActor == GetAttachParentActor()) return;
	UE_LOG(LogTemp,Warning,TEXT("OverlappedActor's Label == %s"),*OtherComp->GetName());
	
	FHitResult HitResult;
	if (!BoxTrace(HitResult))
	{
		return;
	}

	IGetHitInterface* HittedActor = Cast<IGetHitInterface>(HitResult.GetActor());
	if (HittedActor)
	{
		HittedActor->GetHit(this,HitResult.ImpactPoint);
	}
}

bool AWeapon::BoxTrace(FHitResult& HitResult)
{
	FVector TraceStart = BoxTraceStart->GetComponentLocation();
	FVector TraceEnd = BoxTraceEnd->GetComponentLocation();
	
	TArray<AActor*> ActorsToIgnore;
	bool bHit = UKismetSystemLibrary::BoxTraceSingle(this, TraceStart, TraceEnd, FVector(5.f), BoxTraceStart->GetComponentRotation(),
	                                     TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForDuration,
	                                     HitResult, true);
	AActor* Actor = HitResult.GetActor();
	UE_LOG(LogTemp, Warning, TEXT("startChasing"));
	UE_LOG(LogTemp, Warning, TEXT("BoxTrace == %s"),(Actor == nullptr ? (L"None__"):(*Actor->GetActorLabel())));

	return bHit;
}
