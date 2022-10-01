// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/FoodItem.h"

AFoodItem::AFoodItem() :
	HealValue(10.f)
{

}

void AFoodItem::Use(ACharacterController* Character)
{
	if(Character)
	{
		Character->Heal(this, HealValue);
		UE_LOG(LogTemp, Warning, TEXT("Healing"));
	}
}
