// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Chest.h"

#include "Blueprint/UserWidget.h"
#include "Items/Inventory.h"

// Sets default values
AChest::AChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
	Inventory->SetCapacity(10);

}

void AChest::Interact(ACharacterController* Interator)
{
	IIntertableInterface::Interact(Interator);
}

void AChest::Use(ACharacterController* Character)
{
	IIntertableInterface::Use(Character);
}

void AChest::LookAt()
{
	OnOpenInventory.Broadcast();
}