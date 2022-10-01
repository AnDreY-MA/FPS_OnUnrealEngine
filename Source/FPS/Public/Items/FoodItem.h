// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "FoodItem.generated.h"

class ACharacterController;

UCLASS()
class FPS_API AFoodItem : public AItem
{
	GENERATED_BODY()

public:
	AFoodItem();

	virtual void Use(ACharacterController* Character) override;
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Healing", meta=(AllowPrivateAccess="true"))
	float HealValue;
	
};
