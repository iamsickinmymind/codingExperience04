// All rights reserved Dominik Pavlicek

#include "PPuzzleGameInstance.h"

#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"

/* ONLINE SUBSUSTEM INCLUDES */
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

/* PROJECT INCLUDES */
#include "PInGameMenu.h"
#include "PMainMenu.h"

// Replaced with NAME_GameSession system const
//const static FName NAME_GameSession = NAME_GameSession; //TEXT("GameSession");
const static FName SERVER_NAME_KEY = TEXT("ServerCustomName");

UPPuzzleGameInstance::UPPuzzleGameInstance() {

	static ConstructorHelpers::FClassFinder<UPMenuWidget> TempMainMenuClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	static ConstructorHelpers::FClassFinder<UPMenuWidget> TempInGameMenuClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));
		
	if ((!ensure(TempMainMenuClass.Class != nullptr))) {
		UE_LOG(LogTemp, Error, TEXT("UPPuzzleGameInstance cannot find MainMenu Class"))
		return;
	}
	else if (!ensure(TempInGameMenuClass.Class != nullptr)) {
		UE_LOG(LogTemp, Error, TEXT("UPPuzzleGameInstance cannot find InGameMenu Class"))
		return;
	}
	else {

		MainMenuClass = TempMainMenuClass.Class;
		InGameMenuClass = TempInGameMenuClass.Class;
	}
}

void UPPuzzleGameInstance::Init() {

	Super::Init();

	IOnlineSubsystem* ActiveOnlineSubsystem = IOnlineSubsystem::Get();

	if(ActiveOnlineSubsystem != nullptr) {

		SessionInterface = ActiveOnlineSubsystem->GetSessionInterface();

		if (SessionInterface.IsValid()) {

			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPPuzzleGameInstance::OnSessionCreated);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPPuzzleGameInstance::OnSessionDestroyed);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPPuzzleGameInstance::OnFindSessionCompleted);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPPuzzleGameInstance::OnJoinedSessionCompleted);
		}
	}
}

void UPPuzzleGameInstance::LoadMainMenu() {

	if (MainMenuClass != nullptr) {

		MainMenu = Cast<UPMainMenu>(CreateWidget<UPMenuWidget>(this, MainMenuClass));

		if (MainMenu != nullptr) {

			MainMenu->Setup();

			// sets this record as menu interface
			// this way we can use HostServer() fce from GameInstance in MainMenu
			MainMenu->SetMenuInterface(this);
		}
	}
}

void UPPuzzleGameInstance::LoadInGameMenu() {

	if (InGameMenuClass) {

		UPInGameMenu* InGameMenuWidget = Cast<UPInGameMenu>(CreateWidget<UPMenuWidget>(this, InGameMenuClass));

		if (InGameMenuWidget) {

			InGameMenuWidget->Setup();

			InGameMenuWidget->SetMenuInterface(this);
		}
	}
}

void UPPuzzleGameInstance::HostServer(FString ServerName) {

	DesiredServerName = ServerName;

	if (SessionInterface.IsValid()) {

		auto ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession);

		if (ExistingSession != nullptr) {

			SessionInterface->DestroySession(NAME_GameSession);
		}
		else {

			CreateSession();
		}
	}
}

void UPPuzzleGameInstance::JoinServer(const uint32 SessionIndex) {

	if (MainMenu == nullptr) return;
	if (!SessionInterface.IsValid()) return;

	MainMenu->Remove();

	SessionInterface->JoinSession(0, NAME_GameSession, SessionSearch->SearchResults[SessionIndex]);
}

void UPPuzzleGameInstance::ReloadMainMenu() {

	UE_LOG(LogTemp, Warning, TEXT("ReloadMainMenu"))

	if (GetPrimaryPlayerController()) {

		FString MainMenuURL = FString("/Game/Maps/MAP_MainMenu");
		GetPrimaryPlayerController()->ClientTravel("/Game/Maps/MAP_MainMenu", ETravelType::TRAVEL_Absolute);
	}
}

void UPPuzzleGameInstance::RefreshServerList() {

	// make search settins shareable so it can be indexed
	SessionSearch = MakeShareable(new FOnlineSessionSearch());

	if (SessionSearch.IsValid() && SessionInterface.IsValid()) {

		SessionSearch->bIsLanQuery = false;
		SessionSearch->MaxSearchResults = 100;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UPPuzzleGameInstance::CreateSession() {

	if (SessionInterface.IsValid()) {

		FOnlineSessionSettings SessionSettings;

			SessionSettings.NumPublicConnections = 2;
			SessionSettings.bShouldAdvertise = true;
			SessionSettings.bUsesPresence = true;
			SessionSettings.Set(SERVER_NAME_KEY, DesiredServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

			IOnlineSubsystem* ActiveOnlineSubsystem = IOnlineSubsystem::Get();
			if (IOnlineSubsystem::Get()->GetSubsystemName() == FName("NULL")) { SessionSettings.bIsLANMatch = true; }
			else { SessionSettings.bIsLANMatch = false; }

		SessionInterface->CreateSession(0, NAME_GameSession, SessionSettings);
	}
}

void UPPuzzleGameInstance::ExitGame_Desktop() {

	if (GetPrimaryPlayerController()) {

		GetPrimaryPlayerController()->ConsoleCommand("Quit");
	}
}

void UPPuzzleGameInstance::OnSessionCreated(FName SessionName, bool Success) {

	if (!Success) {
		if (GetEngine()) GetEngine()->AddOnScreenDebugMessage(0, 5.f, FColor::Red, FString("OnSessionCreated failed"));
		return;
	}
	if (MainMenu != nullptr) {

		MainMenu->Remove();
	}

	if (GetWorld() != nullptr) {

		GetWorld()->ServerTravel("/Game/Maps/MAP_Lobby?listen");
	}
}

void UPPuzzleGameInstance::OnSessionDestroyed(FName SessionName, bool Success) {

	if (Success) {

		//CreateSession();
	}
}

void UPPuzzleGameInstance::OnFindSessionCompleted(bool Success) {

	if (!Success) {
		if (GetEngine()) GetEngine()->AddOnScreenDebugMessage(0, 5.f, FColor::Red, FString("OnFindSessionCompleted failed"));
		return;
	}

	if (MainMenu != nullptr) {

		TArray<FServerData> ServerData;
		for (const FOnlineSessionSearchResult& Itr : SessionSearch->SearchResults) {

			FServerData Data;
			FString TempName;

			Itr.Session.SessionSettings.Get(SERVER_NAME_KEY, TempName); 

				Data.Name = TempName;
				Data.HostUserName = Itr.Session.OwningUserName;
				Data.MaxPlayers = Itr.Session.SessionSettings.NumPublicConnections;
				Data.CurrentPlayers = Data.MaxPlayers - Itr.Session.NumOpenPublicConnections;

			ServerData.Add(Data);
		}

		MainMenu->SetServerList(ServerData);
	}
}

void UPPuzzleGameInstance::OnJoinedSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type JoinSessionResult) {

	if (!SessionInterface.IsValid()) return;

	FString ConnectString;
	// get connect string by session name
	if (SessionInterface->GetResolvedConnectString(SessionName, ConnectString)) {

		UE_LOG(LogTemp, Error, TEXT("Connected to %s"), *SessionName.ToString())
			GetPrimaryPlayerController()->ClientTravel(ConnectString, ETravelType::TRAVEL_Absolute);
	}
	else UE_LOG(LogTemp, Error, TEXT("Cannot get conect string"))
}