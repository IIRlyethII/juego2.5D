// Copyright Epic Games, Inc. All Rights Reserved.
// KillVolume.cpp

#include "KillVolume.h"
#include "HealthComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Constructor
AKillVolume::AKillVolume()
{
	// Set default values
	PrimaryActorTick.bCanEverTick = false;

	// Create kill box
	KillBox = CreateDefaultSubobject<UBoxComponent>(TEXT("KillBox"));
	KillBox->SetBoxExtent(FVector(200.0f, 200.0f, 200.0f));
	KillBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	RootComponent = KillBox;

	// Set default properties
	bInstantKill = true;
	DamageAmount = 100.0f;
	bRespawnAtPlayerStart = true;
	RespawnDelay = 2.0f;
	PendingRespawnController = nullptr;
}

// Called when the game starts
void AKillVolume::BeginPlay()
{
	Super::BeginPlay();
	
	// Bind overlap event
	KillBox->OnComponentBeginOverlap.AddDynamic(this, &AKillVolume::OnOverlapBegin);
}

// Handle overlap events
void AKillVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the overlapping actor is a character
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (!Character)
	{
		return;
	}

	// Get the player controller
	AController* PlayerController = Character->GetController();
	if (!PlayerController)
	{
		return;
	}

	// Call Blueprint event for custom behavior
	OnPlayerEnterKillVolume(Character);

	// Try to find health component
	UHealthComponent* HealthComp = Character->FindComponentByClass<UHealthComponent>();

	if (bInstantKill)
	{
		// Instant kill - set health to 0 if health component exists
		if (HealthComp)
		{
			HealthComp->TakeDamage(HealthComp->GetCurrentHealth());
		}
	}
	else
	{
		// Apply damage if health component exists
		if (HealthComp)
		{
			HealthComp->TakeDamage(DamageAmount);
		}
	}

	// Handle respawn if enabled
	if (bRespawnAtPlayerStart)
	{
		PendingRespawnController = PlayerController;

		if (RespawnDelay > 0.0f)
		{
			// Respawn after delay
			FTimerHandle RespawnTimerHandle;
			GetWorldTimerManager().SetTimer(RespawnTimerHandle, this,
				&AKillVolume::RespawnPlayer, RespawnDelay, false);
		}
		else
		{
			// Respawn immediately
			RespawnPlayer(PlayerController);
		}
	}
}

// Respawn the player at PlayerStart
void AKillVolume::RespawnPlayer(AController* PlayerController)
{
	// Use pending controller if no parameter provided
	if (!PlayerController && PendingRespawnController)
	{
		PlayerController = PendingRespawnController;
	}

	if (!PlayerController)
	{
		return;
	}

	// Find PlayerStart actor in the level
	AActor* PlayerStartActor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass());
	
	if (!PlayerStartActor)
	{
		// No PlayerStart found, log warning
		UE_LOG(LogTemp, Warning, TEXT("KillVolume: No PlayerStart found in level!"));
		return;
	}

	// Get the possessed pawn
	APawn* PlayerPawn = PlayerController->GetPawn();
	if (PlayerPawn)
	{
		// Reset the player's location to PlayerStart
		PlayerPawn->SetActorLocation(PlayerStartActor->GetActorLocation());
		PlayerPawn->SetActorRotation(PlayerStartActor->GetActorRotation());

		// Reset velocity
		PlayerPawn->GetMovementComponent()->StopMovementImmediately();

		// Reset health if health component exists
		UHealthComponent* HealthComp = PlayerPawn->FindComponentByClass<UHealthComponent>();
		if (HealthComp)
		{
			HealthComp->ResetHealth();
		}
	}

	// Clear pending controller
	PendingRespawnController = nullptr;
}
