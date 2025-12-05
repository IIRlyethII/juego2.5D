// Copyright Epic Games, Inc. All Rights Reserved.
// Runner2DGameMode.h
// Main game mode for the 2.5D runner game
// Manages game flow, score, and level progression

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Runner2DGameMode.generated.h"

/**
 * Game Mode for 2.5D Side-Scrolling Runner
 * Manages gameplay rules, player spawning, and game state.
 * 
 * Blueprint students can inherit to add:
 * - Score system
 * - Enemy spawning
 * - Level progression
 * - Game over conditions
 */
UCLASS(minimalapi)
class ARunner2DGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Constructor
	ARunner2DGameMode();

protected:
	// ---------- Game State ----------

	/** Current player score */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	int32 CurrentScore;

	/** Is the game currently active? */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	bool bGameActive;

public:
	// ---------- Public Functions ----------

	/** 
	 * Add points to the player's score
	 * @param Points - Number of points to add
	 */
	UFUNCTION(BlueprintCallable, Category = "Game State")
	void AddScore(int32 Points);

	/** 
	 * Get the current score
	 */
	UFUNCTION(BlueprintPure, Category = "Game State")
	int32 GetScore() const { return CurrentScore; }

	/** 
	 * Reset the score to zero
	 */
	UFUNCTION(BlueprintCallable, Category = "Game State")
	void ResetScore();

	/** 
	 * Start the game
	 */
	UFUNCTION(BlueprintCallable, Category = "Game State")
	virtual void StartGame();

	/** 
	 * End the game (Game Over)
	 */
	UFUNCTION(BlueprintCallable, Category = "Game State")
	virtual void EndGame();

	// ---------- Blueprint Events ----------

	/** 
	 * Blueprint event called when score changes
	 * Use this to update UI
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Game State")
	void OnScoreChanged(int32 NewScore);

	/** 
	 * Blueprint event called when game starts
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Game State")
	void OnGameStarted();

	/** 
	 * Blueprint event called when game ends
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Game State")
	void OnGameEnded();
};
