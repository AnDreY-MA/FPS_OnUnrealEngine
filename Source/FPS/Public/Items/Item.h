// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IntertableInterface.h"
#include "Items/ItemData.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

struct FItemData;
class ACharacterController;

UCLASS()
class FPS_API AItem : public AActor, public IIntertableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	class UDataTable* DataTableItem;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	FItemData ItemData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ItemMesh;

public:
	virtual void Interact(UPlayerInteractionComponent* Iterator) override;

	virtual void Use(ACharacterController* Character) override;

	virtual void LookAt() override;

	UFUNCTION(BlueprintCallable)
	void SetDataTable(UDataTable* DataTable) { DataTableItem = DataTable; }

};
