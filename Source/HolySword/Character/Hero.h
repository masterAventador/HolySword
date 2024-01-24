// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Hero.generated.h"

class UAttributeComponent;
class AWeapon;
enum class CharacterWeaponState : uint8;
enum class CharacterState : uint8;
class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;



UCLASS()
class HOLYSWORD_API AHero : public ACharacter
{
	GENERATED_BODY()
	friend class UBaseAnimInstance;

/*
 * Variables
 */

private:
	// Components
	UPROPERTY(VisibleAnywhere)
	UBaseAnimInstance* AnimInstance;
	
	UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	UAttributeComponent* AttributeComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY(VisibleAnywhere)
	AWeapon* Weapon;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> ShieldClass;

	UPROPERTY(VisibleAnywhere)
	AWeapon* Shield;

	// States
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	double Velocity;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	CharacterState State;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	CharacterWeaponState WeaponState;

	// Montages
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* GetHitMontage;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* TestComboMontage;

	// Keyboard Actions
	UPROPERTY(EditAnywhere)
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere)
	UInputAction* IALookAction;

	UPROPERTY(EditAnywhere)
	UInputAction* IAMoveAction;

	UPROPERTY(EditAnywhere)
	UInputAction* IAEquipAction;

	UPROPERTY(EditAnywhere)
	UInputAction* IAJumpAction;

	UPROPERTY(EditAnywhere)
	UInputAction* IAAttackAction;
	
	

/*
 * Functions
 */

protected:
	virtual void BeginPlay() override;

	virtual void SpawnWeapon();
	
public:
	AHero();
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
private:
	virtual void SetState(CharacterState NewState);

	virtual void ArmWeapon();

	virtual void UmarmWeapon();

	virtual void SetWeaponCollisionEnabled(bool bEnabled);

protected:
	virtual void AttachActorToSocket(AActor* Actor,const FName& SocketName);

	virtual float PlayAnimMontage(UAnimMontage* AnimMontage, FName SectionName);
	
public:
	virtual void LookAction(const FInputActionValue& Value);

	virtual void MoveActionTriggered(const FInputActionValue& Value);

	virtual void MoveActionEnd(const FInputActionValue& Value);

	virtual void EquipAction(const FInputActionValue& Value);

	virtual void JumpAction(const FInputActionValue& Value);

	virtual void AttackAction(const FInputActionValue& Value);

};
