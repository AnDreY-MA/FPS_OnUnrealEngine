// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"

#include "Item.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACharacterController::ACharacterController() :
	BaseTurnRate(45.f),
	BaseLookRate(45.f),
	TraceDistance(2000.f)
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

void ACharacterController::InteractPressed()
{
	
	
}

void ACharacterController::TraceForwardImplementation()
{
	FVector Location;
	FRotator Rotation;
	FHitResult HitResult;

	GetController()->GetPlayerViewPoint(Location, Rotation);

	FVector Start = Location;
	FVector End = Start + (Rotation.Vector() * TraceDistance);

	FCollisionQueryParams TraceParams;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End,
		ECC_Visibility, TraceParams);

	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false,2.f);
	
	
}

void ACharacterController::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor)
	{
		Interaction = Cast<IInteractInterface>(OtherActor);
		if(Interaction)
		{
			Interaction->Interact();
		}
	}
	
}

void ACharacterController::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
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


