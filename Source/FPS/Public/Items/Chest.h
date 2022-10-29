// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IntertableInterface.h"
#include "GameFramework/Actor.h"
#include "Chest.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenInventory);

UCLASS()
class FPS_API AChest : public AActor, public IIntertableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChest();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chest", meta=(AllowPrivateAccess))
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chest", meta=(AllowPrivateAccess))
	class UInventory* Inventory;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FOnOpenInventory OnOpenInventory;

public:	
	virtual void Interact(ACharacterController* Interator) override;
	virtual void Use(ACharacterController* Character) override;
	virtual void LookAt() override;

};
