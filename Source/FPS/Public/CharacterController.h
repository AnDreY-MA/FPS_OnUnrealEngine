// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractInterface.h"
#include "Items/ItemData.h"
#include "GameFramework/Character.h"
#include "CharacterController.generated.h"

struct FItemData;
class AItem;
class UInventory;
class AFoodItem;

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

	UFUNCTION(BlueprintCallable, Category="TEST")
	void UseItem(TSubclassOf<AItem> ItemSubclass);
	
	void Interact();

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseLookRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bClimbing;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interactive, meta = (AllowPrivateAccess = "true"))
    bool bHoldingItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items", meta = (AllowPrivateAccess = "true"))
	UInventory* Inventory;

public:

	UInventory* GetInventory() { return Inventory; }

	void Heal(AFoodItem* FoodItem, float Value);
	
};
