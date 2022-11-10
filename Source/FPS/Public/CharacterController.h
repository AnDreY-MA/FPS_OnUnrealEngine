// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Items/ItemData.h"
#include "GameFramework/Character.h"
#include "CharacterController.generated.h"

struct FItemData;
class AItem;
class UInventory;
class AFoodItem;
class AWeapon;

UCLASS()
class FPS_API ACharacterController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterController();

protected:

	void MoveForward(float Value);
	void MoveSide(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void StartCrouch();
	void StopCrouch();
	void Attack();

	UFUNCTION(BlueprintCallable)
	void UseItem(TSubclassOf<AItem> ItemSubclass);
	
	void Interact();

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseLookRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bClimbing;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interactive, meta = (AllowPrivateAccess = "true"))
    bool bHoldingItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	class UPlayerInteractionComponent* InteractionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AnimEquiped;

	bool bEquiped;
	
public:
	
	UPlayerInteractionComponent* GetInteractComp() const { return InteractionComponent; }

	bool GetEquiped() const { return bEquiped; }

	void Heal(AFoodItem* FoodItem, float Value);

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(AWeapon* WeaponToEquip);
	UFUNCTION(BlueprintCallable)
	void DropWeapon();
	
};
