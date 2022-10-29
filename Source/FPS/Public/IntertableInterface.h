// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterController.h"
#include "UObject/Interface.h"
#include "IntertableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIntertableInterface : public UInterface
{
	GENERATED_BODY()
};

class ACharacterController;
/**
 * 
 */
class FPS_API IIntertableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Interact(ACharacterController* Interator);
	virtual void Use(ACharacterController* Character);
	virtual void LookAt();
	
};
