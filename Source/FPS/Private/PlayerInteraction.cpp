// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInteraction.h"

#include "Item.h"
#include "Kismet/GameplayStatics.h"

void UPlayerInteraction::TraceForItems()
{
	if(bActiveTraceForItems)
	{
		FHitResult ItemTraceResult;
		FVector HitLocation;
		TraceUnderCrosshair(ItemTraceResult, HitLocation);

		if (ItemTraceResult.bBlockingHit)
		{
			TraceHitItem = Cast<AItem>(ItemTraceResult.GetActor());
			if(TraceHitItem)
			{
				UE_LOG(LogTemp, Warning, TEXT("ITEM_IN"));
			}
			if(TraceHitItemLastFrame)
			{
				if(TraceHitItem != TraceHitItemLastFrame)
				{
					UE_LOG(LogTemp, Warning, TEXT("ITEM_OUT"));
				}
			}

			TraceHitItemLastFrame = TraceHitItem;
		}	
	}
}

void UPlayerInteraction::SetActivateTraceForItems()
{
	bActiveTraceForItems = true;
}

void UPlayerInteraction::DiactivateTraceForItems()
{
	bActiveTraceForItems = false;
}

void UPlayerInteraction::PickupObject(UCameraComponent* PlayerCamera, USceneComponent* Hand)
{
	if(TraceHitItem)
	{
		TraceHitItem->Pickup(PlayerCamera, Hand);
	}
}

bool UPlayerInteraction::TraceUnderCrosshair(FHitResult& OutHitResult, FVector& OutHitLocation)
{
	FVector2D VieportSize;
	if(GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(VieportSize);
	}

	FVector2D CrosshairLocation(
		VieportSize.X / 2.f, VieportSize.Y / 2.f);
	FVector CrosshairWorldPosition;
	FVector CrosshairWorldDirection;

	bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(
		UGameplayStatics::GetPlayerController(this, 0),
		CrosshairLocation,
		CrosshairWorldPosition,
		CrosshairWorldDirection);

	if(bScreenToWorld)
	{
		const FVector Start = CrosshairWorldPosition;
		const FVector End = Start + CrosshairWorldDirection * 5000.f;
		OutHitLocation = End;

		GetWorld()->LineTraceSingleByChannel(
			OutHitResult,
			Start,
			End,
			ECollisionChannel::ECC_Visibility);
		if(OutHitResult.bBlockingHit)
		{
			OutHitLocation = OutHitResult.Location;
			return true;
		}
	}
	return false;
}
