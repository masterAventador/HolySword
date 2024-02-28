// Fill out your copyright notice in the Description page of Project Settings.


#include "Hero.h"

#include "BaseAnimInstance.h"
#include "AttributeComponent.h"
#include "HolySword/Weapon/Weapon.h"
#include "Enums.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"


AHero::AHero():State(CharacterState::Idle),WeaponState(CharacterWeaponState::Unarmed)
{
	PrimaryActorTick.bCanEverTick = true;
	
	bUseControllerRotationPitch = bUseControllerRotationRoll = bUseControllerRotationYaw = false;

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 500.f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f,500.f,0.f);
	GetCharacterMovement()->JumpZVelocity = 600.f;

	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>("Attributes");

}

void AHero::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance = Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance());
	
	AddControllerPitchInput(15.f);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext,0);
		}
	}

	SpawnWeapon();
	UmarmWeapon();
}

void AHero::SetState(CharacterState NewState)
{
	if (State != NewState)
	{
		State = NewState;
	}
}

void AHero::ArmWeapon()
{
	if (!Weapon) return;
	AttachActorToSocket(Weapon,CharacterSocketName::WeaponSocketName);
	WeaponState = CharacterWeaponState::Armed;
	
	if (!Shield) return;
	AttachActorToSocket(Shield,CharacterSocketName::ShieldSocketName);
}

void AHero::UmarmWeapon()
{
	if (!Weapon) return;
	AttachActorToSocket(Weapon,CharacterSocketName::WeaponBackSocketName);
	WeaponState = CharacterWeaponState::Unarmed;
	
	if (!Shield) return;
	AttachActorToSocket(Shield,CharacterSocketName::ShieldBackSocketName);
}

void AHero::SetWeaponCollisionEnabled(bool bEnabled)
{
	if (!Weapon) return;
	Weapon->SetCollisionEnabled(bEnabled);
}

void AHero::SpawnWeapon()
{
	if (WeaponClass)
	{
		Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass);
	}

	return;
	if (ShieldClass)
	{
		Shield = GetWorld()->SpawnActor<AWeapon>(ShieldClass);
	}
}

void AHero::AttachActorToSocket(AActor* Actor, const FName& SocketName)
{
	if (!Actor) return;
	const USkeletalMeshSocket* Socket = GetMesh()->GetSocketByName(SocketName);
	if (!Socket) return;
	Socket->AttachActor(Actor,GetMesh());
}

void AHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Velocity = GetVelocity().Size2D();
}

void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(IARightMouseAction,ETriggerEvent::Started,this,&ThisClass::RightMouseAction);
		EnhancedInputComponent->BindAction(IALookAction,ETriggerEvent::Triggered,this,&ThisClass::LookAction);
		EnhancedInputComponent->BindAction(IAMoveAction,ETriggerEvent::Triggered,this,&ThisClass::MoveActionTriggered);
		EnhancedInputComponent->BindAction(IAMoveAction,ETriggerEvent::Completed,this,&ThisClass::MoveActionEnd);
		EnhancedInputComponent->BindAction(IAEquipAction,ETriggerEvent::Started,this,&ThisClass::EquipAction);
		EnhancedInputComponent->BindAction(IAJumpAction,ETriggerEvent::Started,this,&ThisClass::JumpAction);
		EnhancedInputComponent->BindAction(IAAttackAction,ETriggerEvent::Started,this,&ThisClass::AttackAction);
	}
}

void AHero::RightMouseAction(const FInputActionValue& Value)
{
	
}

void AHero::LookAction(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void AHero::MoveActionTriggered(const FInputActionValue& Value)
{
	SetState(CharacterState::Run);
	
	FVector2D MoveVector = Value.Get<FVector2D>();
	FRotationMatrix RotationMatrix = FRotationMatrix(FRotator(0.f,GetControlRotation().Yaw,0.f));
	FVector ForwardVector = RotationMatrix.GetUnitAxis(EAxis::X);
	FVector RightVector = RotationMatrix.GetUnitAxis(EAxis::Y);
	AddMovementInput(ForwardVector,MoveVector.X);
	AddMovementInput(RightVector,MoveVector.Y);
}

void AHero::MoveActionEnd(const FInputActionValue& Value)
{
	SetState(CharacterState::Idle);
}

void AHero::EquipAction(const FInputActionValue& Value)
{
	if (WeaponState == CharacterWeaponState::Unarmed)
	{
		PlayMontage(EquipMontage,MontageSectionName::Arm);
	} else
	{
		PlayMontage(EquipMontage,MontageSectionName::Umarm);
	}
}

void AHero::JumpAction(const FInputActionValue& Value)
{
	Super::Jump();
}

void AHero::AttackAction(const FInputActionValue& Value)
{
	if (!TestComboMontage) return;
	if (AnimInstance->Montage_IsPlaying(TestComboMontage)) return;
	PlayMontage(TestComboMontage,"Combo01");
}

