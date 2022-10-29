// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

struct FItemData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

	void SetCapacity(int32 Amount);
	void AddItemToMap(FName ItemName, int32 Quantity);
	
	UFUNCTION(BlueprintCallable)
	bool RemoveItem(FName ItemName, int32 Quantity);

	UFUNCTION(BlueprintCallable)
	void SwapItem(UInventory* TargetInventory, FName NameItem, int32 Quantity);

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta=(AllowPrivateAccess))
	TMap<FName, int32> ItemsInventory;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta=(AllowPrivateAccess))
	int32 Capacity;
		
};
