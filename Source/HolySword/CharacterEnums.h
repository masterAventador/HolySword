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

struct CharacterSocketName
{
	inline const static FName WeaponBackSocketName = "weapon_b";
	inline const static FName ShieldBackSocketName = "Shield_b";
	inline const static FName WeaponSocketName = "weapon_r";
	inline const static FName ShieldSocketName = "shield_l";
};

struct CharacterEquipMontageSectionNames
{
	inline const static FName Arm = "Arm";
	inline const static FName Umarm = "Unarm";
};

