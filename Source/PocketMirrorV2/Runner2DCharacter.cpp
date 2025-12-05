// Copyright Epic Games, Inc. All Rights Reserved.
// Runner2DCharacter.cpp

#include "Runner2DCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

// Constructor
ARunner2DCharacter::ARunner2DCharacter()
{
	// Set default values
	WalkSpeed = 300.0f;
	RunSpeed = 600.0f;
	bIsRunning = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement for 2.5D
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 0.0f);
	
	// Constrain movement to XZ plane (side-scrolling)
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));
	
	// Set initial movement speed
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	
	// Configure jumping
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create camera boom (pulls towards the player if there's a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f; // Camera distance
	CameraBoom->bDoCollisionTest = false; // Don't check for collisions
	CameraBoom->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f)); // Side view angle
	CameraBoom->bUsePawnControlRotation = false; // Don't rotate with controller
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;

	// Create side view camera
	SideViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCamera->bUsePawnControlRotation = false; // Camera does not rotate
}

// Called when the game starts or when spawned
void ARunner2DCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called to bind functionality to input
void ARunner2DCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings using Enhanced Input
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARunner2DCharacter::Move);

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ARunner2DCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ARunner2DCharacter::StopJumping);
	}
}

// Handle horizontal movement input
void ARunner2DCharacter::Move(const FInputActionValue& Value)
{
	// Input is a float value for left-right movement
	float MovementValue = Value.Get<float>();

	if (Controller != nullptr && MovementValue != 0.0f)
	{
		// Add movement along the X axis (forward/backward in world space = left/right in side view)
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), MovementValue);
		
		// Optional: Flip character sprite based on direction
		// Students can override this in Blueprint if needed
		if (MovementValue < 0.0f)
		{
			// Moving left
			SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));
		}
		else if (MovementValue > 0.0f)
		{
			// Moving right
			SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}
}

// Handle jump input
void ARunner2DCharacter::Jump()
{
	Super::Jump();
	// Additional jump logic can be added in Blueprint
}

// Handle jump release
void ARunner2DCharacter::StopJumping()
{
	Super::StopJumping();
	// Additional logic can be added in Blueprint
}
