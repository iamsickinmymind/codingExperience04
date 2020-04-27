// All rights reserved Dominik Pavlicek

#include "PLobbyGameMode.h"

APLobbyGameMode::APLobbyGameMode() {

	bUseSeamlessTravel = true;
}

void APLobbyGameMode::PostLogin(APlayerController* NewPlayer) {

	Super::PostLogin(NewPlayer);

	NumberOfPlayers++;

	if(NumberOfPlayers >= PlayersToStart) {

		if (GetWorld() != nullptr) {

			GetWorld()->ServerTravel("/Game/Maps/MAP_PuzzleMap?listen");
		}
	}
}

void APLobbyGameMode::Logout(AController* Exiting) {

	Super::Logout(Exiting);

	NumberOfPlayers--;
}
