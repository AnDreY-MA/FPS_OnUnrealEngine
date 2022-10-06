// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"

#include "Components/CapsuleComponent.h"
#include "CharacterController.h"
#include "Items/Inventory.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleComponent->SetupAttachment(GetRootComponent());
	
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	FItemData* It = DataTableItem->FindRow<FItemData>(Name, "");

	ItemData.Name = It->Name;
	
	MeshComponent->SetStaticMesh(It->Mesh);
	
}

void AItem::Interact(class ACharacterController* Interator)
{
	if(Interator)
	{
		Interator->GetInventory()->AddItem(ItemData);
		Interator->GetInventory()->AddItemToMap(Name, 1);
	}

	Destroy();

}

void AItem::Use(ACharacterController* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("Using Item"));
}


