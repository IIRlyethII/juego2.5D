// Copyright Epic Games, Inc. All Rights Reserved.
// HealthPickup.cpp

#include "HealthPickup.h"
#include "HealthComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"

// Constructor
AHealthPickup::AHealthPickup()
{
	// Set default values
	PrimaryActorTick.bCanEverTick = false;

	// Create collision sphere
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->InitSphereRadius(50.0f);
	CollisionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	RootComponent = CollisionSphere;

	// Create mesh component
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetupAttachment(CollisionSphere);
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Set default pickup properties
	HealAmount = 25.0f;
	bShouldRespawn = true;
	RespawnDelay = 10.0f;
	bIsActive = true;
}

// Called when the game starts
void AHealthPickup::BeginPlay()
{
	Super::BeginPlay();
	
	// Bind overlap event
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AHealthPickup::OnOverlapBegin);
}

// Handle overlap events
void AHealthPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult)
{
	// Ignore if pickup is not active
	if (!bIsActive)
	{
		return;
	}

	// Check if the overlapping actor is a character
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (!Character)
	{
		return;
	}

	// Try to find a health component on the character
	UHealthComponent* HealthComp = Character->FindComponentByClass<UHealthComponent>();
	if (!HealthComp)
	{
		return;
	}

	// Only heal if the character is not at full health
	if (HealthComp->GetCurrentHealth() < HealthComp->GetMaxHealth())
	{
		// Heal the character
		HealthComp->Heal(HealAmount);

		// Call Blueprint event for visual/audio feedback
		OnPickupCollected(Character);

		// Deactivate the pickup
		DeactivatePickup();

		// Schedule respawn if enabled
		if (bShouldRespawn)
		{
			GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, 
				&AHealthPickup::RespawnPickup, RespawnDelay, false);
		}
		else
		{
			// Destroy the pickup if it shouldn't respawn
			Destroy();
		}
	}
}

// Deactivate the pickup (hide and disable collision)
void AHealthPickup::DeactivatePickup()
{
	bIsActive = false;
	
	// Hide the pickup
	SetActorHiddenInGame(true);
	
	// Disable collision
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Respawn the pickup (show and enable collision)
void AHealthPickup::RespawnPickup()
{
	bIsActive = true;
	
	// Show the pickup
	SetActorHiddenInGame(false);
	
	// Enable collision
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	// Call Blueprint event for spawn effects
	OnPickupRespawned();
}

// Manually set pickup active state
void AHealthPickup::SetPickupActive(bool bActive)
{
	if (bActive)
	{
		RespawnPickup();
	}
	else
	{
		DeactivatePickup();
	}
}
