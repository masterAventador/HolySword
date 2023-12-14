// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"


ABaseCharacter::ABaseCharacter()
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
	
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	AddControllerPitchInput(15.f);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext,0);
		}
	}
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(IALookAction,ETriggerEvent::Triggered,this,&ThisClass::LookActionFunc);
		EnhancedInputComponent->BindAction(IAMoveAction,ETriggerEvent::Triggered,this,&ThisClass::MoveActionFunc);
	}

}

void ABaseCharacter::LookActionFunc(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void ABaseCharacter::MoveActionFunc(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();
	FRotationMatrix RotationMatrix = FRotationMatrix(FRotator(0.f,GetControlRotation().Yaw,0.f));
	FVector ForwardVector = RotationMatrix.GetUnitAxis(EAxis::X);
	FVector RightVector = RotationMatrix.GetUnitAxis(EAxis::Y);
	AddMovementInput(ForwardVector,MoveVector.X);
	AddMovementInput(RightVector,MoveVector.Y);
}

