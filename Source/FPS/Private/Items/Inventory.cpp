// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Inventory.h"

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

void UInventory::AddItemToMap(FName ItemName, int32 Quantity)
{
	int32 Count = ItemsInventory.FindOrAdd(ItemName);
	Count += Quantity;
	
	ItemsInventory.Add(ItemName, Count);
	
	OnInventoryUpdated.Broadcast();
}

bool UInventory::RemoveItem(FName ItemName, int32 Quantity)
{
	int32 FindItem = ItemsInventory.FindRef(ItemName);
	
	if(Quantity <= FindItem)
	{
		if((FindItem - Quantity) == 0)
		{
			ItemsInventory.Remove(ItemName);
		}
		else
		{
			ItemsInventory.Add(ItemName, 0);
		}
	}

	return true;
}

void UInventory::SwapItem(UInventory* TargetInventory, FName NameItem, int32 Quantity)
{
	if (RemoveItem(NameItem, Quantity))
	{
		TargetInventory->AddItemToMap(NameItem, Quantity);
	}
	
}


