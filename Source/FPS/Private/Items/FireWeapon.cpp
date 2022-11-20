// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/FireWeapon.h"
#include "CharacterController.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Items/Bullet.h"
#include "Tasks/GameplayTask_SpawnActor.h"

AFireWeapon::AFireWeapon() :
	AmmoType(EWeaponAmmoType::EAT_PISTOL),
	Ammo(10),
	MagazineCapacity(10)
{
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}

void AFireWeapon::Fire(ACharacterController* Character)
{
	const USkeletalMeshSocket* MuzzleSocket = WeaponMesh->GetSocketByName("Muzzle");
	if(MuzzleSocket)
	{
		const APlayerController* Controller = Cast<APlayerController>(Character->GetController());
		const FVector SocketLocation = MuzzleSocket->GetSocketLocation(WeaponMesh);
		const FRotator SocketRotator = Controller->PlayerCameraManager->GetCameraRotation();
		const FActorSpawnParameters ActorSpawnParameters;
		GetWorld()->SpawnActor<ABullet>(Bullet, SocketLocation, SocketRotator, ActorSpawnParameters);
		Ammo = Ammo - 1;
	}
}

void AFireWeapon::Interact(UPlayerInteractionComponent* Iterator)
{
	Super::Interact(Iterator);
}

void AFireWeapon::Use(ACharacterController* Character)
{
	Fire(Character);
}

void AFireWeapon::LookAt()
{
	Super::LookAt();
}
