// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapon.h"
#include "CharacterController.h"

AWeapon::AWeapon()
{
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	//SetRootComponent(SkeletalMeshComponent);
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	FItemData* It = DataTableItem->FindRow<FItemData>(Name, "");

	ItemData.Name = It->Name;
	if (It->WeaponMesh)
	{
		SkeletalMeshComponent->SetSkeletalMesh(It->WeaponMesh);
	}
}

void AWeapon::Interact(ACharacterController* Interator)
{
	Super::Interact(Interator);
}

void AWeapon::Use(ACharacterController* Character)
{
	Super::Use(Character);
}

void AWeapon::LookAt()
{
	Super::LookAt();
}
