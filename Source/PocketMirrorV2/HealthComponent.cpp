// Copyright Epic Games, Inc. All Rights Reserved.
// HealthComponent.cpp

#include "HealthComponent.h"

// Constructor
UHealthComponent::UHealthComponent()
{
	// Set default values
	PrimaryComponentTick.bCanEverTick = false; // No need to tick every frame
	
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
	bIsDead = false;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialize health to max at start
	CurrentHealth = MaxHealth;
	bIsDead = false;
}

// Apply damage to the actor
void UHealthComponent::TakeDamage(float Damage)
{
	// Ignore if already dead or damage is negative
	if (bIsDead || Damage <= 0.0f)
	{
		return;
	}

	// Apply damage (negative delta)
	UpdateHealth(-Damage);
}

// Heal the actor
void UHealthComponent::Heal(float HealAmount)
{
	// Ignore if dead or heal amount is negative
	if (bIsDead || HealAmount <= 0.0f)
	{
		return;
	}

	// Apply healing (positive delta)
	UpdateHealth(HealAmount);
}

// Get health as percentage (0.0 to 1.0)
float UHealthComponent::GetHealthPercent() const
{
	if (MaxHealth <= 0.0f)
	{
		return 0.0f;
	}
	
	return CurrentHealth / MaxHealth;
}

// Reset health to maximum
void UHealthComponent::ResetHealth()
{
	bIsDead = false;
	CurrentHealth = MaxHealth;
	
	// Broadcast health changed event
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth, 0.0f);
}

// Internal function to update health and trigger events
void UHealthComponent::UpdateHealth(float Delta)
{
	// Store old health for comparison
	float OldHealth = CurrentHealth;
	
	// Update current health (clamp between 0 and max)
	CurrentHealth = FMath::Clamp(CurrentHealth + Delta, 0.0f, MaxHealth);
	
	// Only broadcast if health actually changed
	if (CurrentHealth != OldHealth)
	{
		// Broadcast health changed event
		OnHealthChanged.Broadcast(CurrentHealth, MaxHealth, Delta);
		
		// Check for death
		if (CurrentHealth <= 0.0f && !bIsDead)
		{
			bIsDead = true;
			OnDeath.Broadcast();
		}
	}
}
