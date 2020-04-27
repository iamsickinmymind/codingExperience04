// All rights reserved Dominik Pavlicek

#include "PLobbyGameMode.h"
#include "TimerManager.h"

#include "PPuzzleGameInstance.h"

APLobbyGameMode::APLobbyGameMode() {

	bUseSeamlessTravel = true;
	PlayersToStart = 5;
	MinimumPlayersToStart = 3;
	LobbyTimeout = 10;
	bLoopLobyTimer = true;
}

void APLobbyGameMode::BeginPlay() {

	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(LobbyTimeoutTimerHandle, this, &APLobbyGameMode::OnLobbyTimeoutExpired, LobbyTimeout, bLoopLobyTimer);
}

void APLobbyGameMode::PostLogin(APlayerController* NewPlayer) {

	Super::PostLogin(NewPlayer);

	NumberOfPlayers++;

	if (NumberOfPlayers >= PlayersToStart) {

		StartGame();
	}
}

void APLobbyGameMode::Logout(AController* Exiting) {

	Super::Logout(Exiting);

	NumberOfPlayers--;
}

void APLobbyGameMode::OnLobbyTimeoutExpired() {

	if (NumberOfPlayers >= MinimumPlayersToStart) {

		GetWorldTimerManager().ClearTimer(LobbyTimeoutTimerHandle);

		StartGame();
	}
}

void APLobbyGameMode::StartGame() {

	if (GetWorld() != nullptr) {

		UPPuzzleGameInstance* TempGameInstance = Cast<UPPuzzleGameInstance>(GetGameInstance());

		if (TempGameInstance != nullptr) {

			TempGameInstance->StartSession();

			GetWorld()->ServerTravel("/Game/Maps/MAP_PuzzleMap?listen");
		}
	}
}