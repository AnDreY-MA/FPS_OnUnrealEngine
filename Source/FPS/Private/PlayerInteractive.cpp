// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInteractive.h"

#include "Components/BoxComponent.h"

// Sets default values for this component's properties
UPlayerInteractive::UPlayerInteractive()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Hand = CreateDefaultSubobject<UBoxComponent>(TEXT("Hand"));
	Hand->SetupAttachment(GetAttachmentRoot());
}


// Called when the game starts
void UPlayerInteractive::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerInteractive::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

