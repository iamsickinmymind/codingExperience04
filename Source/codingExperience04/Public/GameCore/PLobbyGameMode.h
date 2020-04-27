// All rights reserved Dominik Pavlicek

#pragma once

#include "CoreMinimal.h"
#include "codingExperience04GameMode.h"
#include "PLobbyGameMode.generated.h"

/**
 * (P)uzzle Game Mode.
 */
UCLASS()
class CODINGEXPERIENCE04_API APLobbyGameMode : public AcodingExperience04GameMode
{
	GENERATED_BODY()
	
public:

	APLobbyGameMode();

	virtual void BeginPlay() override;
	
	virtual void PostLogin(APlayerController* NewPlayer) override;
	
	virtual void Logout(AController* Exiting) override;

protected:

	void OnLobbyTimeoutExpired();

private:

	void StartGame();

protected:

	// Amount players required to start the game
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
	int32 PlayersToStart;

	// Minimum players required to start the game even if PlayersToStart are not all met
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
	int32 MinimumPlayersToStart;

	// Time period after which the lobby travels to Main game
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
	int32 LobbyTimeout;

	// Defines whether timer loops or not.
	// If true: every 'LobbyTimeout' period timer restarts.
	// If false: Timer runs only once.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
	bool bLoopLobyTimer;

private:

	int32 NumberOfPlayers = 0;
	FTimerHandle LobbyTimeoutTimerHandle;
};
