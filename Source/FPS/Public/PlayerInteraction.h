// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "PlayerInteraction.generated.h"

UENUM(BlueprintType)
enum class EHandState : uint8
{
	EHS_Grab UMETA(DisplayName = "GrabHand"),
	EHS_Click UMETA(DisplayName = "ClickHand"),
	EHS_Pickup UMETA(DisplayName = "PickupHand"),

	EHS_Default UMETA(DisplayName = "Point")
};

/**
 * 
 */
UCLASS()
class FPS_API UPlayerInteraction : public UPhysicsHandleComponent
{
	GENERATED_BODY()
	
public:
	UPlayerInteraction();
	
	void TraceForItems();
	void SetActivateTraceForItems();
	void DiactivateTraceForItems();
	void PickupObject(class UCameraComponent* PlayerCamera, USceneComponent* Hand);
	EHandState GetHandState() const;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interactive, meta = (AllowPrivateAccess = "true"))
	class AItem* TraceHitItemLastFrame = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interactive, meta = (AllowPrivateAccess = "true"))
	AItem* TraceHitItem = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interactive, meta = (AllowPrivateAccess = "true"))
	EHandState HandState;

	bool bActiveTraceForItems;
	
	bool TraceUnderCrosshair(FHitResult& OutHitResult, FVector& OutHitLocation);
	
};
