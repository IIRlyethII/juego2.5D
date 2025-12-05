// Copyright Epic Games, Inc. All Rights Reserved.
// Runner2DGameMode.cpp

#include "Runner2DGameMode.h"
#include "Runner2DCharacter.h"
#include "UObject/ConstructorHelpers.h"

// Constructor
ARunner2DGameMode::ARunner2DGameMode()
{
	// Set default pawn class to our custom character
	// Students should override this in Blueprint to use their BP_Character
	DefaultPawnClass = ARunner2DCharacter::StaticClass();

	// Initialize game state
	CurrentScore = 0;
	bGameActive = true;
}

// Add points to score
void ARunner2DGameMode::AddScore(int32 Points)
{
	if (Points <= 0)
	{
		return;
	}

	// Add points
	CurrentScore += Points;

	// Broadcast score change event
	OnScoreChanged(CurrentScore);
}

// Reset score to zero
void ARunner2DGameMode::ResetScore()
{
	CurrentScore = 0;
	OnScoreChanged(CurrentScore);
}

// Start the game
void ARunner2DGameMode::StartGame()
{
	bGameActive = true;
	ResetScore();

	// Call Blueprint event
	OnGameStarted();
}

// End the game
void ARunner2DGameMode::EndGame()
{
	bGameActive = false;

	// Call Blueprint event
	OnGameEnded();
}
