// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInteraction.h"

#include "GrabObject.h"
#include "Kismet/GameplayStatics.h"

UPlayerInteraction::UPlayerInteraction() :
	HandState(EHandState::EHS_Default)
{

}

void UPlayerInteraction::Interact()
{
	
}

void UPlayerInteraction::TraceForItems()
{
	if(bActiveTraceForItems)
	{
		FHitResult ItemTraceResult;
		FVector HitLocation;
		TraceUnderCrosshair(ItemTraceResult, HitLocation);

		if (ItemTraceResult.bBlockingHit)
		{
			TraceHitItem = Cast<AGrabObject>(ItemTraceResult.GetActor());
			if(TraceHitItem)
			{
				HandState = EHandState::EHS_Grab;
			}
			if(TraceHitItemLastFrame)
			{
				if(TraceHitItem != TraceHitItemLastFrame)
				{
					HandState = EHandState::EHS_Default;
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
	HandState = EHandState::EHS_Default;
}

void UPlayerInteraction::PickupObject(UCameraComponent* PlayerCamera, USceneComponent* Hand)
{
	if(TraceHitItem)
	{
		TraceHitItem->Pickup(PlayerCamera, Hand);
	}
}

EHandState UPlayerInteraction::GetHandState() const
{
	return HandState;
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
