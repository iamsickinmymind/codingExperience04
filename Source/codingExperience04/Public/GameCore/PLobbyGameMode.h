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
	
	virtual void PostLogin(APlayerController* NewPlayer) override;
	
	virtual void Logout(AController* Exiting) override;

protected:

	// Minimum players required to start the game
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
	int32 PlayersToStart;

private:

	int32 NumberOfPlayers = 0;
	
};
