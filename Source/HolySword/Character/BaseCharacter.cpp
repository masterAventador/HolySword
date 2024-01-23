// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "BaseAnimInstance.h"
#include "AttributeComponent.h"
#include "HolySword/Weapon/BaseWeapon.h"
#include "CharacterEnums.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"


ABaseCharacter::ABaseCharacter():State(CharacterState::Idle),WeaponState(CharacterWeaponState::Unarmed)
{

	bUseControllerRotationPitch = bUseControllerRotationRoll = bUseControllerRotationYaw = false;
	
	PrimaryActorTick.bCanEverTick = true;
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

void ABaseCharacter::BeginPlay()
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

void ABaseCharacter::SetState(CharacterState NewState)
{
	if (State != NewState)
	{
		State = NewState;
	}
}

void ABaseCharacter::ArmWeapon()
{
	if (!Weapon) return;
	AttachActorToSocket(Weapon,CharacterSocketName::WeaponSocketName);
	WeaponState = CharacterWeaponState::Armed;
	
	if (!Shield) return;
	AttachActorToSocket(Shield,CharacterSocketName::ShieldSocketName);
}

void ABaseCharacter::UmarmWeapon()
{
	if (!Weapon) return;
	AttachActorToSocket(Weapon,CharacterSocketName::WeaponBackSocketName);
	WeaponState = CharacterWeaponState::Unarmed;
	
	if (!Shield) return;
	AttachActorToSocket(Shield,CharacterSocketName::ShieldBackSocketName);
}

void ABaseCharacter::SetWeaponCollisionEnabled(bool bEnabled)
{
	if (!Weapon) return;
	Weapon->SetCollisionEnabled(bEnabled);
}

void ABaseCharacter::SpawnWeapon()
{
	if (WeaponClass)
	{
		Weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);
	}
	if (ShieldClass)
	{
		Shield = GetWorld()->SpawnActor<ABaseWeapon>(ShieldClass);
	}
}

void ABaseCharacter::AttachActorToSocket(AActor* Actor, const FName& SocketName)
{
	if (!Actor) return;
	const USkeletalMeshSocket* Socket = GetMesh()->GetSocketByName(SocketName);
	if (!Socket) return;
	Socket->AttachActor(Actor,GetMesh());
}

float ABaseCharacter::PlayAnimMontage(UAnimMontage* AnimMontage, FName SectionName)
{
	if (!AnimMontage) return 0;
	return Super::PlayAnimMontage(AnimMontage,1,SectionName);
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Velocity = GetVelocity().Size2D();
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(IALookAction,ETriggerEvent::Triggered,this,&ThisClass::LookAction);
		EnhancedInputComponent->BindAction(IAMoveAction,ETriggerEvent::Triggered,this,&ThisClass::MoveActionTriggered);
		EnhancedInputComponent->BindAction(IAMoveAction,ETriggerEvent::Completed,this,&ThisClass::MoveActionEnd);
		EnhancedInputComponent->BindAction(IAEquipAction,ETriggerEvent::Started,this,&ThisClass::EquipAction);
		EnhancedInputComponent->BindAction(IAJumpAction,ETriggerEvent::Started,this,&ThisClass::JumpAction);
		EnhancedInputComponent->BindAction(IAAttackAction,ETriggerEvent::Started,this,&ThisClass::AttackAction);
	}
}

void ABaseCharacter::LookAction(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void ABaseCharacter::MoveActionTriggered(const FInputActionValue& Value)
{
	SetState(CharacterState::Run);
	
	FVector2D MoveVector = Value.Get<FVector2D>();
	FRotationMatrix RotationMatrix = FRotationMatrix(FRotator(0.f,GetControlRotation().Yaw,0.f));
	FVector ForwardVector = RotationMatrix.GetUnitAxis(EAxis::X);
	FVector RightVector = RotationMatrix.GetUnitAxis(EAxis::Y);
	AddMovementInput(ForwardVector,MoveVector.X);
	AddMovementInput(RightVector,MoveVector.Y);
}

void ABaseCharacter::MoveActionEnd(const FInputActionValue& Value)
{
	SetState(CharacterState::Idle);
}

void ABaseCharacter::EquipAction(const FInputActionValue& Value)
{
	if (WeaponState == CharacterWeaponState::Unarmed)
	{
		PlayAnimMontage(EquipMontage,CharacterMontageSectionName::Arm);
	} else
	{
		PlayAnimMontage(EquipMontage,CharacterMontageSectionName::Umarm);
	}
}

void ABaseCharacter::JumpAction(const FInputActionValue& Value)
{
	Super::Jump();
}

void ABaseCharacter::AttackAction(const FInputActionValue& Value)
{
	if (!TestComboMontage) return;
	if (AnimInstance->Montage_IsPlaying(TestComboMontage)) return;
	PlayAnimMontage(TestComboMontage,"Combo01");
}

