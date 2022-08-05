// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "CharacterController.h"
#include "IDetailTreeNode.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AItem::AItem() :
	bHolding(false),
	bGravity(true)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetSimulatePhysics(true);
	ItemMesh->SetEnableGravity(true);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetRootComponent(ItemMesh);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(ItemMesh);
	CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	AreaSphere->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bHolding && HoldingComponent)
	{
		SetActorLocation(HoldingComponent->GetComponentLocation());
	}

}

void AItem::Interact()
{
	
}

void AItem::Pickup(UCameraComponent* PlayerCamera, USceneComponent* HoldComp)
{
	HoldingComponent = HoldComp;
	
	bHolding = !bHolding;
	bGravity = !bGravity;
	ItemMesh->SetEnableGravity(bGravity);
	ItemMesh->SetSimulatePhysics(bHolding ? false : true);
	ItemMesh->SetCollisionEnabled(bHolding ? ECollisionEnabled::NoCollision : ECollisionEnabled::QueryAndPhysics);

	if(!bHolding)
	{
		FVector ForwardVector = PlayerCamera->GetForwardVector();
		ItemMesh->AddForce(ForwardVector * 10000 * ItemMesh->GetMass());
	}
}




