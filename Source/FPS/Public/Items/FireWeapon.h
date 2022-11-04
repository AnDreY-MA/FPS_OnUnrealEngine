// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapon.h"
#include "Items/WeaponAmmoType.h"
#include "FireWeapon.generated.h"

UCLASS()
class FPS_API AFireWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	AFireWeapon();

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo", meta = (AllowPrivateAccess = "true"))
	EWeaponAmmoType AmmoType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo", meta = (AllowPrivateAccess = "true"))
	int32 Ammo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo", meta = (AllowPrivateAccess = "true"))
	int32 MagazineCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABullet> Bullet;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
    FVector MuzzleOffset;

	void Fire(ACharacterController* Character);

public:
	
	virtual void Interact(UPlayerInteractionComponent* Iterator) override;

	virtual void Use(ACharacterController* Character) override;

	virtual void LookAt() override;
	
};
