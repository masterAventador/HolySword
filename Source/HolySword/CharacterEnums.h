#pragma once

UENUM(BlueprintType)
enum class CharacterState : uint8
{
	Idle UMETA(DisplayName="Idle"),
	Run UMETA(DisplayName="Run"),
	Crouch UMETA(DisplayName="Crouch"),
	Attack UMETA(DisplayName="Attack"),

	Max UMETA(DisplayName="DefaultMax")
};

UENUM(BlueprintType)
enum class CharacterWeaponState : uint8
{
	Unarmed UMETA(DisplayName="Unarmed"),
	Armed UMETA(DisplayName="Armed"),
	
	Max UMETA(DisplayName="DefaultMax")
};

