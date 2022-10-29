// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/FireWeapon.h"
#include "CharacterController.h"

AFireWeapon::AFireWeapon() :
	AmmoType(EAmmoType::EAT_PISTOL),
	Ammo(10),
	MagazineCapacity(10)
{
	
}

void AFireWeapon::Interact(ACharacterController* Interator)
{
	Super::Interact(Interator);
}

void AFireWeapon::Use(ACharacterController* Character)
{
	Super::Use(Character);
}

void AFireWeapon::LookAt()
{
	Super::LookAt();
}
