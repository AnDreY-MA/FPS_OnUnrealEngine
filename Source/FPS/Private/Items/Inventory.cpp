// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Inventory.h"
#include "Items/ItemData.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInventory::SetCapacity(int32 Amount)
{
	Capacity += Amount;
}

void UInventory::AddItem(FItemData Item)
{
	Items.Add(Item);
	OnInventoryUpdated.Broadcast();
}