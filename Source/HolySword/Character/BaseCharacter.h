// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UBaseAttributeComponent;
class ABaseWeapon;
enum class CharacterWeaponState : uint8;
enum class CharacterState : uint8;
class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;



UCLASS()
class HOLYSWORD_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()
	friend class UBaseAnimInstance;

/*
 * Variables
 */

private:
	// Components
	UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	UBaseAttributeComponent* AttributeComponent;

	UPROPERTY(EditAnywhere,meta=(AllowPrivateAccess=true))
	TSubclassOf<ABaseWeapon> WeaponClass;

	UPROPERTY(VisibleAnywhere,meta=(AllowPrivateAccess=true))
	ABaseWeapon* Weapon;

	UPROPERTY(EditAnywhere,meta=(AllowPrivateAccess=true))
	TSubclassOf<ABaseWeapon> ShieldClass;

	UPROPERTY(VisibleAnywhere,meta=(AllowPrivateAccess=true))
	ABaseWeapon* Shield;

	// States
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	double Velocity;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	CharacterState State;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	CharacterWeaponState WeaponState;

	// Montages
	UPROPERTY(EditDefaultsOnly,meta=(AllowPrivateAccess=true))
	UAnimMontage* EquipMontage;

	// Keyboard Actions
	UPROPERTY(EditAnywhere)
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere)
	UInputAction* IALookAction;

	UPROPERTY(EditAnywhere)
	UInputAction* IAMoveAction;

	UPROPERTY(EditAnywhere)
	UInputAction* IAEquipAction;
	

/*
 * Functions
 */
private:
	virtual void SetState(CharacterState NewState);

	virtual void ArmWeapon();

	virtual void UmarmWeapon();

protected:
	virtual void BeginPlay() override;

	virtual void SpawnWeapon();

	virtual void AttachActorToSocket(AActor* Actor,const FName& SocketName);
public:
	ABaseCharacter();
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void LookAction(const FInputActionValue& Value);

	virtual void MoveActionStart(const FInputActionValue& Value);

	virtual void MoveActionEnd(const FInputActionValue& Value);

	virtual void EquipAction(const FInputActionValue& Value);

};
