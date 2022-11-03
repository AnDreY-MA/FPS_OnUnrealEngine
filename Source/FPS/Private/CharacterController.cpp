// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"

#include "IntertableInterface.h"
#include "PlayerInteractionComponent.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Items/Inventory.h"
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
	Health(90.f),
	bHoldingItem(false),
	bClimbing(false),
	bEquiped(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCamera->SetupAttachment(GetRootComponent());
	FirstPersonCamera->bUsePawnControlRotation = true;

	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
	Inventory->SetCapacity(10);

	InteractionComponent = CreateDefaultSubobject<UPlayerInteractionComponent>(TEXT("InteractionComponent"));

	AmmoMagazine.Add(EWeaponAmmoType::EAT_PISTOL, 20);

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
	if(Value > 0 && FoodItem && Health < 100)
	{
		Health += Value;
		UE_LOG(LogTemp, Warning, TEXT("Healing"));
	}
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
	if(EquippedWeapon)
	{
		EquippedWeapon->Use(this);
	}

	/*UKismetSystemLibrary KismetSystemLibrary;
	KismetSystemLibrary.MoveComponentTo()*/
}

void ACharacterController::EquipWeapon(AWeapon* WeaponToEquip)
{
	if(WeaponToEquip)
	{
		const USkeletalMeshSocket* HandSocket = GetMesh()->GetSocketByName(FName("WeaponSocket"));
		if(HandSocket)
		{
			HandSocket->AttachActor(WeaponToEquip, GetMesh());
			bEquiped = true;
		}
		EquippedWeapon = WeaponToEquip;
	}
}
void ACharacterController::DropWeapon()
{
	if(EquippedWeapon)
	{
		EquippedWeapon->Destroy();
		bEquiped = false;
	}
	
}

void ACharacterController::UseItem(TSubclassOf<AItem> ItemSubclass)
{
	if(ItemSubclass)
	{
		if(AItem* UsingItem = ItemSubclass.GetDefaultObject())
		{
			UsingItem->Use(this);
		}
	}
	
}

void ACharacterController::Interact()
{
	const FVector Start = FirstPersonCamera->GetComponentLocation();
	const FVector End = Start + FirstPersonCamera->GetForwardVector() * 500.f;

	FHitResult HitResult;
	FCollisionQueryParams Params;
	///Params.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);
	if(IIntertableInterface* Interface = Cast<IIntertableInterface>(HitResult.GetActor()))
	{
		Interface->Interact(this);
	}
}
