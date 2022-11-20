// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "PlayerInteractionComponent.generated.h"

class AWeapon;
class UInventory;
class ACharacterController;
class AItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGrabObject, FHitResult, HitResult);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UPlayerInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInteractionComponent();

	void Interact(const ACharacterController* PlayerCharacter, const class UCameraComponent* CameraComponent);
	bool EquipWeapon(USkeletalMeshComponent* Hand, AWeapon* WeaponToEquip);
	bool DropWeapon();
	void UseItem(ACharacterController* PlayerCharacter, TSubclassOf<AItem> ItemSubclass);
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	float InterectDistance;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items", meta = (AllowPrivateAccess = "true"))
	UInventory* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items", meta = (AllowPrivateAccess = "true"))
	AWeapon* EquippedWeapon;

	UPROPERTY(BlueprintAssignable)
	FOnGrabObject OnGrabObject;

	FHitResult TraceObject(const UCameraComponent* CameraComponent);

public:
	UInventory* GetInventory() { return Inventory; }

	AWeapon* GetWeapon() const { return EquippedWeapon; }

};
