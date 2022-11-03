// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "Bullet.generated.h"

UCLASS()
class FPS_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bullet", meta=(AllowPrivateAccess))
	class USphereComponent* SphereComponent;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bullet", meta=(AllowPrivateAccess))
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bullet", meta=(AllowPrivateAccess))
	class UProjectileMovementComponent* ProjectileMovementComponent;
	
};
