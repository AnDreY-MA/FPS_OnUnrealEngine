// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"

#include "CharacterController.h"
#include "Engine/DataTable.h"
#include "Items/Inventory.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);
	
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	FItemData* It = DataTableItem->FindRow<FItemData>(Name, "");

	ItemData.Name = It->Name;
	if (It->Mesh)
	{
		MeshComponent->SetStaticMesh(It->Mesh);
	}
	
}

void AItem::Interact(class ACharacterController* Interator)
{
	if(Interator)
	{
		Interator->GetInventory()->AddItemToMap(Name, 1);
	}

	Destroy();

}

void AItem::Use(ACharacterController* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("Using Item"));
}

void AItem::LookAt()
{
	IIntertableInterface::LookAt();
}


