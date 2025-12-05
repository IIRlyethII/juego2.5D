// Copyright Epic Games, Inc. All Rights Reserved.
// Runner2DCharacter.h
// Base C++ class for the 2.5D side-scrolling character
// Students can create Blueprints inheriting from this class

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Runner2DCharacter.generated.h"

// Forward declarations
class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;

/**
 * Base character class for 2.5D side-scrolling gameplay.
 * Movement is constrained to a single horizontal axis (left-right).
 * Camera is fixed in a side view.
 * 
 * Blueprint students should inherit from this to add game-specific logic.
 */
UCLASS(config=Game)
class POCKETMIRRORV2_API ARunner2DCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Constructor
	ARunner2DCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ---------- Input Actions ----------
	
	/** Called for horizontal movement input */
	void Move(const FInputActionValue& Value);

	/** Called for jump input */
	void Jump() override;

	/** Called when jump is released */
	void StopJumping() override;

	// ---------- Components ----------

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* SideViewCamera;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	// ---------- Enhanced Input ----------

	/** MappingContext for input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	// ---------- Movement Settings ----------

	/** Maximum walk speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|2.5D")
	float WalkSpeed;

	/** Maximum run speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|2.5D")
	float RunSpeed;

	/** Whether the character is currently running */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement|2.5D")
	bool bIsRunning;

public:
	// ---------- Public Getters ----------

	/** Returns SideViewCamera subobject */
	FORCEINLINE UCameraComponent* GetSideViewCamera() const { return SideViewCamera; }
	
	/** Returns CameraBoom subobject */
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};
