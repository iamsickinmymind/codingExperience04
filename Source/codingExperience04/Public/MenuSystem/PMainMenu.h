// All rights reserved Dominik Pavlicek

#pragma once

#include "CoreMinimal.h"

#include "PMenuWidget.h"

#include "PMainMenu.generated.h"

class UButton;
class UEditableText;
class UScrollBox;
class UWidgetSwitcher;
class UPServerRow;

USTRUCT()
struct FServerData
{

	GENERATED_BODY()

	FString Name;
	FString HostUserName;
	uint16 CurrentPlayers;
	uint16 MaxPlayers;
};

/**
 * (P)uzzle User Widget Main Class.
 * Button names in C++ must correspond with WBP button names.
 * Keep in mind to do not change WBP button names
 */
UCLASS()
class CODINGEXPERIENCE04_API UPMainMenu : public UPMenuWidget
{
	GENERATED_BODY()

public:

	UPMainMenu();

	void SetServerList(TArray<FServerData> ServerData);

	void UpdateRows();

	FORCEINLINE void SetSelectedIndex(uint32 NewIndex) { SelectedIndex = NewIndex; };

protected:

	virtual bool Initialize() override;

	UFUNCTION()
	void OnHostGameClicked();

	UFUNCTION()
	void OnJoinGameClicked();

	UFUNCTION()
	void OnJoinServerClicked();

	UFUNCTION()
	void OnCancelJoinClicked();

	UFUNCTION()
	void OnExitGameClicked();
	
protected:

	// To bind this button the WBP must have a button with the same name
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* HostGameButton = nullptr;

	// To bind this button the WBP must have a button with the same name
	// Join Game Button to open JoinGame menu
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* JoinGameButton = nullptr;

	// To bind this button the WBP must have a button with the same name
	// Join Server Button to join the server
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* JoinServerButton = nullptr;

	// To bind this button the WBP must have a button with the same name
	// Cancels JoinGame menu and returns you to MainMenu
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* CancelJoinButton = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ExitGameButton = nullptr;

	// To bind this switcher the WBP must have a switcher with the same name
	// Switcher which holds Main menu and Join Game menu
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher = nullptr;

	// To bind this widget the WBP must have a widget with the same name
	// JoinGameMenu root component
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UWidget* JoinGameMenu;

	// To bind this widget the WBP must have a widget with the same name
	// MainMenu root component
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UWidget* MainMenu;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* ServerListScrollBox = nullptr;

	// To bind this TextBox the WBP must have a TextBox with the same name
	// TexytBox to write IP Address in
	// 	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	// 	UEditableText* EditableTextBox_IPAddress = nullptr;

private:

	TSubclassOf<UPServerRow> ServerRowsClass = nullptr;
	TOptional <uint32> SelectedIndex;
};
