// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapon.h"
#include "CharacterController.h"

AWeapon::AWeapon()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	WeaponMesh->SetupAttachment(GetRootComponent());
	ItemMesh->SetSimulatePhysics(true);
	WeaponMesh->SetSimulatePhysics(true);

}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	FItemData* It = DataTableItem->FindRow<FItemData>(Name, "");

	ItemData.Name = It->Name;
	if (It->WeaponMesh)
	{
		WeaponMesh->SetSkeletalMesh(It->WeaponMesh);
	}
}

void AWeapon::Equip()
{
	ItemMesh->SetSimulatePhysics(false);
	ItemMesh->SetEnableGravity(false);
	ItemMesh->SetCollisionResponseToChannels(ECR_Ignore);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

void AWeapon::Drop()
{
	ItemMesh->SetSimulatePhysics(true);
	ItemMesh->SetEnableGravity(true);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AWeapon::Interact(UPlayerInteractionComponent* Iterator)
{
	Super::Interact(Iterator);
}

void AWeapon::Use(ACharacterController* Character)
{
	Super::Use(Character);
}

void AWeapon::LookAt()
{
	Super::LookAt();
}
