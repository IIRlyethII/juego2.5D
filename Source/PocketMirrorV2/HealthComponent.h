// Copyright Epic Games, Inc. All Rights Reserved.
// HealthComponent.h
// Manages health for any actor (character, enemies, etc.)
// Students can extend this in Blueprints for custom behavior

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

// Delegate for health changed events (can be used in Blueprints)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHealthChanged, float, Health, float, MaxHealth, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

/**
 * Health Component - Attach to any actor that needs health management.
 * Handles current health, max health, damage, healing, and death.
 * 
 * Blueprint Events:
 * - OnHealthChanged: Broadcast when health changes
 * - OnDeath: Broadcast when health reaches zero
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class POCKETMIRRORV2_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Constructor
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// ---------- Health Properties ----------

	/** Current health value */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float CurrentHealth;

	/** Maximum health value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;

	/** Is the actor currently dead? */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	bool bIsDead;

public:	
	// ---------- Public Functions ----------

	/** 
	 * Apply damage to this actor
	 * @param Damage - Amount of damage to apply (positive value)
	 */
	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(float Damage);

	/** 
	 * Heal this actor
	 * @param HealAmount - Amount of health to restore (positive value)
	 */
	UFUNCTION(BlueprintCallable, Category = "Health")
	void Heal(float HealAmount);

	/** 
	 * Get current health percentage (0.0 to 1.0)
	 * Useful for health bars in UI
	 */
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	/** 
	 * Check if actor is alive
	 */
	UFUNCTION(BlueprintPure, Category = "Health")
	bool IsAlive() const { return !bIsDead; }

	/** 
	 * Get current health value
	 */
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetCurrentHealth() const { return CurrentHealth; }

	/** 
	 * Get max health value
	 */
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetMaxHealth() const { return MaxHealth; }

	/** 
	 * Reset health to maximum (useful for respawning)
	 */
	UFUNCTION(BlueprintCallable, Category = "Health")
	void ResetHealth();

	// ---------- Events ----------

	/** Event broadcast when health changes */
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChanged OnHealthChanged;

	/** Event broadcast when actor dies (health reaches 0) */
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDeath OnDeath;

private:
	/** Internal helper to update health and broadcast events */
	void UpdateHealth(float Delta);
};
