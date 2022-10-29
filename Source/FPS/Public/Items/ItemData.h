// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AItem> ItemClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMesh* Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USkeletalMesh* WeaponMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTexture2D* Image;

};