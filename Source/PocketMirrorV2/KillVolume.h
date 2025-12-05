// Copyright Epic Games, Inc. All Rights Reserved.
// KillVolume.h
// Volume that resets the player to PlayerStart when touched
// Useful for pits, hazards, or out-of-bounds areas

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KillVolume.generated.h"

// Forward declarations
class UBoxComponent;

/**
 * Kill Volume Actor
 * When a player touches this volume, they are teleported back to PlayerStart.
 * Can optionally damage or kill the player.
 * 
 * Blueprint students can customize:
 * - Volume size
 * - Whether it kills or just teleports
 * - Visual feedback (particles, sounds)
 * - Damage amount
 */
UCLASS()
class POCKETMIRRORV2_API AKillVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Constructor
	AKillVolume();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// ---------- Components ----------

	/** Box collision for detecting overlaps */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* KillBox;

	// ---------- Kill Volume Properties ----------

	/** Should the volume instantly kill the player? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kill Volume")
	bool bInstantKill;

	/** Damage to apply if not instant kill */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kill Volume", meta = (EditCondition = "!bInstantKill"))
	float DamageAmount;

	/** Should the player respawn at PlayerStart after being killed? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kill Volume")
	bool bRespawnAtPlayerStart;

	/** Delay before respawning (in seconds) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kill Volume", meta = (EditCondition = "bRespawnAtPlayerStart"))
	float RespawnDelay;

	// ---------- Overlap Events ----------

	/** Called when something enters the kill volume */
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	// ---------- Blueprint Events ----------

	/**
	 * Blueprint event called when a player enters the kill volume
	 * Use this for death animations, sounds, or particles
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Kill Volume")
	void OnPlayerEnterKillVolume(AActor* Player);

private:
	/** Internal function to respawn the player */
	void RespawnPlayer(AController* PlayerController);

	/** Store player controller for respawn timer */
	UPROPERTY()
	AController* PendingRespawnController;
};
