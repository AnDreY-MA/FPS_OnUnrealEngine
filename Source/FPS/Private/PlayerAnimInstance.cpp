// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

#include "CharacterController.h"

void UPlayerAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	ACharacterController* Player = Cast<ACharacterController>(TryGetPawnOwner());
	if(Player != nullptr)
	{
		FVector Velocity = Player->GetVelocity();
		Velocity.Z = 0;
		Speed = Velocity.Size();
		bEquiped = Player->GetEquiped();
	}
}
