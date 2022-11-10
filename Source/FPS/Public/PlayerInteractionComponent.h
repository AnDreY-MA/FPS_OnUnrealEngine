// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/ArrowComponent.h"
#include "CollisionQueryParams.h"
#include "PlayerInteractionComponent.generated.h"

class AWeapon;
class UInventory;
class ACharacterController;
class AItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UPlayerInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInteractionComponent();

	void Interact(const ACharacterController* PlayerCharacter, const class UCameraComponent* CameraComponent);
	bool EquipWeapon(const ACharacterController* PlayerCharacter, AWeapon* WeaponToEquip);
	bool DropWeapon();
	void UseItem(ACharacterController* PlayerCharacter, TSubclassOf<AItem> ItemSubclass);
private:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items", meta = (AllowPrivateAccess = "true"))
	UInventory* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items", meta = (AllowPrivateAccess = "true"))
	AWeapon* EquippedWeapon;

public:
	UInventory* GetInventory() { return Inventory; }

	AWeapon* GetWeapon() const { return EquippedWeapon; }

};
