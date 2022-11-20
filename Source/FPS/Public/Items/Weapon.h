// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Weapon.generated.h"

UCLASS()
class FPS_API AWeapon : public AItem
{
	GENERATED_BODY()

public:
	AWeapon();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* WeaponMesh;

public:

	void Equip();
	void Drop();
	
	virtual void Interact(UPlayerInteractionComponent* Iterator) override;

	virtual void Use(ACharacterController* Character) override;

	virtual void LookAt() override;
	
};
