// Copyright Epic Games, Inc. All Rights Reserved.
// HealthPickup.h
// Pickup actor that heals the player on overlap
// Students can create Blueprints from this for different healing items

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthPickup.generated.h"

// Forward declarations
class USphereComponent;
class UStaticMeshComponent;

/**
 * Health Pickup Actor
 * When overlapped by a character with a HealthComponent, it heals them.
 * After healing, the pickup can either respawn after a delay or be destroyed.
 * 
 * Blueprint students can inherit to customize:
 * - Visual mesh/sprite
 * - Heal amount
 * - Sound effects
 * - Particle effects
 */
UCLASS()
class POCKETMIRRORV2_API AHealthPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Constructor
	AHealthPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ---------- Components ----------

	/** Collision sphere for overlap detection */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* CollisionSphere;

	/** Visual representation of the pickup */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PickupMesh;

	// ---------- Pickup Properties ----------

	/** Amount of health this pickup restores */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float HealAmount;

	/** Should the pickup respawn after being collected? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	bool bShouldRespawn;

	/** Time in seconds before respawning (if bShouldRespawn is true) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (EditCondition = "bShouldRespawn"))
	float RespawnDelay;

	/** Is the pickup currently active? */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	bool bIsActive;

	// ---------- Overlap Events ----------

	/** Called when something overlaps this actor */
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult& SweepResult);

	// ---------- Blueprint Events ----------

	/** 
	 * Blueprint event called when pickup is collected
	 * Use this to play sounds, spawn particles, etc.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Pickup")
	void OnPickupCollected(AActor* Collector);

	/** 
	 * Blueprint event called when pickup respawns
	 * Use this to play spawn effects
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Pickup")
	void OnPickupRespawned();

private:
	/** Handle for managing respawn timer */
	FTimerHandle RespawnTimerHandle;

	/** Internal function to deactivate the pickup */
	void DeactivatePickup();

	/** Internal function to respawn the pickup */
	void RespawnPickup();

public:
	/** 
	 * Manually activate/deactivate the pickup
	 * Useful for resetting levels or creating pickup waves
	 */
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetPickupActive(bool bActive);
};
