// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

#include "CharacterController.h"

void UPlayerAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	const auto* Player = Cast<ACharacterController>(TryGetPawnOwner());
	if(Player)
	{
		const FVector Velocity = Player->GetVelocity();
		//Velocity.Z = 0;
		Speed = Velocity.Size();
		Direction = CalculateDirection(Velocity, Player->GetActorRotation());
	}
}
