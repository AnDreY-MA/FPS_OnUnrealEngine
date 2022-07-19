// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACharacterController::ACharacterController() :
	BaseTurnRate(45.f),
	BaseLookRate(45.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCamera->SetupAttachment(GetRootComponent());
	FirstPersonCamera->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void ACharacterController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

