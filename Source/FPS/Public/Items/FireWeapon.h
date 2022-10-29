// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapon.h"
#include "Items/AmmoType.h"
#include "FireWeapon.generated.h"



UCLASS()
class FPS_API AFireWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	AFireWeapon();


private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo", meta = (AllowPrivateAccess = "true"))
	EAmmoType AmmoType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo", meta = (AllowPrivateAccess = "true"))
	int32 Ammo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo", meta = (AllowPrivateAccess = "true"))
	int32 MagazineCapacity;

public:
	virtual void Interact(ACharacterController* Interator) override;

	virtual void Use(ACharacterController* Character) override;

	virtual void LookAt() override;
	
};
