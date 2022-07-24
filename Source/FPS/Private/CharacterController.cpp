// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"

#include "Item.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACharacterController::ACharacterController() :
	BaseTurnRate(45.f),
	BaseLookRate(45.f),
	bShouldTraceForItems(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCamera->SetupAttachment(GetRootComponent());
	FirstPersonCamera->bUsePawnControlRotation = true;
	
	InteractBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractiveBox"));
	InteractBox->SetupAttachment(GetRootComponent());

	Hand = CreateDefaultSubobject<USphereComponent>(TEXT("Hand"));
	Hand->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ACharacterController::BeginPlay()
{
	Super::BeginPlay();

    InteractBox->OnComponentBeginOverlap.AddDynamic(this, &ACharacterController::OnSphereBeginOverlap);
	InteractBox->OnComponentEndOverlap.AddDynamic(this, &ACharacterController::OnSphereEndOverlap);
}

// Called every frame
void ACharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TraceForItems();

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
	

}

void ACharacterController::MoveForward(float Value)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation {0, Rotation.Yaw, 0};

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
	
}

void ACharacterController::MoveSide(float Value)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation {0, Rotation.Yaw, 0 };

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
	
}

void ACharacterController::Turn(float Value)
{
	AddControllerYawInput(Value * 45.f * GetWorld()->GetDeltaSeconds());
	
}

void ACharacterController::LookUp(float Value)
{
	AddControllerPitchInput(Value * 45.f * GetWorld()->GetDeltaSeconds());
	
}

void ACharacterController::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor)
	{
		Interaction = Cast<IInteractInterface>(OtherActor);
		if(Interaction)
		{
			Interaction->Interact();
			bShouldTraceForItems = true;
		}
	}
	
}

void ACharacterController::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor)
	{
		Interaction = Cast<IInteractInterface>(OtherActor);
		if(Interaction)
		{
			Interaction->Interact();
			bShouldTraceForItems = false;
		}
	}
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

// Interaction with Item
bool ACharacterController::TraceUnderCrosshair(FHitResult& OutHitResult, FVector& OutHitLocation)
{
	FVector2D VieportSize;
	if(GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(VieportSize);
	}

	FVector2D CrosshairLocation(
		VieportSize.X / 2.f, VieportSize.Y / 2.f);
	FVector CrosshairWorldPosition;
	FVector CrosshairWorldDirection;

	bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(
		UGameplayStatics::GetPlayerController(this, 0),
		CrosshairLocation,
		CrosshairWorldPosition,
		CrosshairWorldDirection);

	if(bScreenToWorld)
	{
		const FVector Start = CrosshairWorldPosition;
		const FVector End = Start + CrosshairWorldDirection * 5000.f;
		OutHitLocation = End;

		GetWorld()->LineTraceSingleByChannel(
			OutHitResult,
			Start,
			End,
			ECollisionChannel::ECC_Visibility);
		if(OutHitResult.bBlockingHit)
		{
			OutHitLocation = OutHitResult.Location;
			return true;
		}
	}
	return false;
}

void ACharacterController::TraceForItems()
{
	if(bShouldTraceForItems)
	{
		FHitResult ItemTraceResult;
		FVector HitLocation;
		TraceUnderCrosshair(ItemTraceResult, HitLocation);

		if (ItemTraceResult.bBlockingHit)
		{
			TraceHitItem = Cast<AItem>(ItemTraceResult.GetActor());
			if(TraceHitItem)
			{
				UE_LOG(LogTemp, Warning, TEXT("ITEM_IN"));
			}
			if(TraceHitItemLastFrame)
			{
				if(TraceHitItem != TraceHitItemLastFrame)
				{
					UE_LOG(LogTemp, Warning, TEXT("ITEM_OUT"));
				}
			}

			TraceHitItemLastFrame = TraceHitItem;
		}	
	}
}


