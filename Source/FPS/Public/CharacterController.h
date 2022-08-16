// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractInterface.h"
#include "PlayerInteraction.h"
#include "GameFramework/Character.h"
#include "CharacterController.generated.h"

UCLASS()
class FPS_API ACharacterController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveSide(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void StartCrouch();
	void StopCrouch();
	void CreateUserWidget();
	
	void PickupObject();
	void DropObject();

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseLookRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bClimbing;
	
	// Interaction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interactive, meta = (AllowPrivateAccess = "true"))
	UPlayerInteraction* InteractionClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interactive, meta = (AllowPrivateAccess = "true"))
    class UBoxComponent* InteractBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interactive, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Hand;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interactive, meta = (AllowPrivateAccess = "true"))
    bool bHoldingItem;
	
	IInteractInterface* Interaction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> DefaultWidget;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE EHandState GetStateHand() const { return InteractionClass->GetHandState(); }
	
};
