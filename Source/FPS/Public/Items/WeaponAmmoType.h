#pragma once

UENUM(BlueprintType)
enum class EWeaponAmmoType : uint8
{
	EAT_PISTOL UMETA(DisplayName = "Pistol"),
	EAT_RIFLE UMETA(DisplayName = "AssaultRifle"),

	EAT_MAX UMETA(DisaplayName = "DefaultMax")
};