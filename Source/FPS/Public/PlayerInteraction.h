// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "PlayerInteraction.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UPlayerInteraction : public UPhysicsHandleComponent
{
	GENERATED_BODY()
	
public:
	void TraceForItems();
	void SetActivateTraceForItems();
	void DiactivateTraceForItems();
	void PickupObject(class UCameraComponent* PlayerCamera, USceneComponent* Hand);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interactive, meta = (AllowPrivateAccess = "true"))
	class AItem* TraceHitItemLastFrame = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interactive, meta = (AllowPrivateAccess = "true"))
	AItem* TraceHitItem = nullptr;
	
	bool TraceUnderCrosshair(FHitResult& OutHitResult, FVector& OutHitLocation);

	bool bActiveTraceForItems;
	
};
