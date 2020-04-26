// All rights reserved Dominik Pavlicek

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "MenuSystem/MenuInterface.h"

#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "PPuzzleGameInstance.generated.h"

class UPMainMenu;
class UUserWidget;

/**
 * (P)uzzle Game Instance.
 */
UCLASS()
class CODINGEXPERIENCE04_API UPPuzzleGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	
	UPPuzzleGameInstance();

	virtual void Init() override;

	UFUNCTION(Exec)
	void HostServer(FString ServerName) override;

	UFUNCTION(Exec)
	void JoinServer(const uint32 SessionIndex) override;

	UFUNCTION(BlueprintCallable, Category = "Main Menu")
	void LoadMainMenu();

	UFUNCTION(BlueprintCallable, Category = "Main Menu")
	void LoadInGameMenu();

	virtual void ReloadMainMenu() override;
	virtual void RefreshServerList() override;
	virtual void ExitGame_Desktop() override;

private:

	TSubclassOf<UUserWidget> MainMenuClass = nullptr;
	TSubclassOf<UUserWidget> InGameMenuClass = nullptr;
	UPMainMenu* MainMenu = nullptr;
	IOnlineSessionPtr SessionInterface;
	TSharedPtr < FOnlineSessionSearch > SessionSearch;
	FString DesiredServerName;

	void OnSessionCreated(FName SessionName, bool Success);
	void OnSessionDestroyed(FName SessionName, bool Success);
	void OnFindSessionCompleted(bool Success);
	void CreateSession();
	void OnJoinedSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type JoinSessionResult);
};