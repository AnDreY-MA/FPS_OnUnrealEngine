// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInteractionComponent.h"

#include "BlueprintEditor.h"
#include "IntertableInterface.h"
#include "Items/Inventory.h"
#include "Items/Weapon.h"
#include "Items/Item.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UPlayerInteractionComponent::UPlayerInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Inventory = CreateDefaultSubobject<UInventory>("InventoryIter");
	Inventory->SetCapacity(10);
	
}

void UPlayerInteractionComponent::Interact(const ACharacterController* PlayerCharacter, const UCameraComponent* CameraComponent)
{
	const FVector Start = CameraComponent->GetComponentLocation();
	const FVector End = Start + CameraComponent->GetForwardVector() * 500.0f;

	FHitResult HitResult;
	FCollisionQueryParams Params;
	//Params.AddIgnoredActor(PlayerCharacter);
	
	//GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility))
	{
		if(IIntertableInterface* Interface = Cast<IIntertableInterface>(HitResult.GetActor()))
		{
			Interface->Interact(this);
		}
	}
	
}

bool UPlayerInteractionComponent::EquipWeapon(const ACharacterController* PlayerCharacter, AWeapon* WeaponToEquip)
{
	if(!WeaponToEquip) return false;
	
	const USkeletalMeshSocket* HandSocket = PlayerCharacter->GetMesh()->GetSocketByName(FName("WeaponSocket"));
	if(!HandSocket) return false;

	HandSocket->AttachActor(WeaponToEquip, PlayerCharacter->GetMesh());
	EquippedWeapon = WeaponToEquip;
	return true;

}

bool UPlayerInteractionComponent::DropWeapon()
{
	if(!EquippedWeapon) return false;

	EquippedWeapon->Destroy();
	EquippedWeapon = nullptr;
	return true;

}

void UPlayerInteractionComponent::UseItem(ACharacterController* PlayerCharacter, TSubclassOf<AItem> ItemSubclass)
{
	if(ItemSubclass)
	{
		if(AItem* UsingItem = ItemSubclass.GetDefaultObject())
		{
			UsingItem->Use(PlayerCharacter);
		}
	}
}