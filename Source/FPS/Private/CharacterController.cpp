// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"

#include "PlayerInteractionComponent.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Items/Item.h"
#include "Items/Weapon.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACharacterController::ACharacterController() :
	BaseTurnRate(45.f),
	BaseLookRate(45.f),
	bHoldingItem(false),
	bClimbing(false),
	bEquiped(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCamera->SetupAttachment(GetRootComponent());
	FirstPersonCamera->bUsePawnControlRotation = true;

	InteractionComponent = CreateDefaultSubobject<UPlayerInteractionComponent>(TEXT("InteractionComponent"));
	
}

// Called to bind functionality to input
void ACharacterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterController::MoveForward);
	PlayerInputComponent->BindAxis("MoveSide", this, &ACharacterController::MoveSide);
	
	PlayerInputComponent->BindAxis("Turn", this, &ACharacterController::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacterController::LookUp);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ACharacterController::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ACharacterController::StopCrouch);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ACharacterController::Interact);
	PlayerInputComponent->BindAction("DropWeapon", IE_Pressed, this, &ACharacterController::DropWeapon);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ACharacterController::Attack);
	
}

void ACharacterController::Heal(AFoodItem* FoodItem, float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Healing"));

}

void ACharacterController::MoveForward(float Value)
{
	if(bClimbing == false)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation {0, Rotation.Yaw, 0};

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
	
}

void ACharacterController::MoveSide(float Value)
{
	if(bClimbing == false)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation {0, Rotation.Yaw, 0 };

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
	
}

void ACharacterController::Turn(float Value)
{
	AddControllerYawInput(Value * 45.f * GetWorld()->GetDeltaSeconds());
	
}

void ACharacterController::LookUp(float Value)
{
	AddControllerPitchInput(Value * 45.f * GetWorld()->GetDeltaSeconds());
	
}

void ACharacterController::StartCrouch()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(44.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	ACharacter::Crouch();
	
}

void ACharacterController::StopCrouch()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(88.f);
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	ACharacter::UnCrouch();
	
}

void ACharacterController::Attack()
{
	if(InteractionComponent->GetWeapon())
	{
		InteractionComponent->GetWeapon()->Use(this);
	}

	/*UKismetSystemLibrary KismetSystemLibrary;
	KismetSystemLibrary.MoveComponentTo()*/
}

void ACharacterController::EquipWeapon(AWeapon* WeaponToEquip)
{
	bEquiped = InteractionComponent->EquipWeapon(this, WeaponToEquip);
}

void ACharacterController::DropWeapon()
{
	bEquiped = !InteractionComponent->DropWeapon();
	
}

void ACharacterController::UseItem(TSubclassOf<AItem> ItemSubclass)
{
	InteractionComponent->UseItem(this, ItemSubclass);
	
}

void ACharacterController::Interact()
{
	InteractionComponent->Interact(this, FirstPersonCamera);
}
