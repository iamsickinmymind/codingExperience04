// All rights reserved Dominik Pavlicek

#include "PMainMenu.h"

#include "UObject/ConstructorHelpers.h"

#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/WidgetSwitcher.h"

#include "PServerRow.h"

UPMainMenu::UPMainMenu() {

	static ConstructorHelpers::FClassFinder<UPServerRow> TempServerRowsClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));
	if ((!ensure(TempServerRowsClass.Class != nullptr))) {
		UE_LOG(LogTemp, Error, TEXT("UPPuzzleGameInstance cannot find MainMenu Class"))
		return;
	}
	ServerRowsClass = TempServerRowsClass.Class;
}

bool UPMainMenu::Initialize() {

	bool bSuccess = Super::Initialize();

	if (!bSuccess || !HostGameButton || !JoinGameButton) return !bSuccess;

	HostGameButton->OnClicked.AddDynamic(this, &UPMainMenu::OnHostGameClicked);
	JoinGameButton->OnClicked.AddDynamic(this, &UPMainMenu::OnJoinGameClicked);
	JoinServerButton->OnClicked.AddDynamic(this, &UPMainMenu::OnJoinServerClicked);
	CancelJoinButton->OnClicked.AddDynamic(this, &UPMainMenu::OnCancelJoinClicked);
	ExitGameButton->OnClicked.AddDynamic(this, &UPMainMenu::OnExitGameClicked);

	return true;
}

void UPMainMenu::OnHostGameClicked() {

	if (MenuInterface) {

		MenuInterface->HostServer();
	}
}

void UPMainMenu::OnJoinGameClicked() {

	if (MenuSwitcher && JoinGameMenu) { 

		MenuSwitcher->SetActiveWidget(JoinGameMenu);
		MenuInterface->RefreshServerList();
	}
	else return;
}

void UPMainMenu::OnJoinServerClicked() {

	/* if I dont have selected index or I have invalid one dont try to connect */
	if(!(SelectedIndex.IsSet()) || SelectedIndex.GetValue() < 0) {

		UE_LOG(LogTemp, Warning, TEXT("SelectedIndex Not Set"))
		return;
	}

	if(MenuInterface != nullptr) {

		MenuInterface->JoinServer(SelectedIndex.GetValue());
	}
}

void UPMainMenu::OnCancelJoinClicked() {

	if (MenuSwitcher && MainMenu) {

		MenuSwitcher->SetActiveWidget(MainMenu);

		if(ServerListScrollBox) {

			ServerListScrollBox->ClearChildren();
		}
	}
}

void UPMainMenu::OnExitGameClicked() {

	if(MenuInterface) {

		MenuInterface->ExitGame_Desktop();
	}
}

void UPMainMenu::SetServerList(TArray<FString> ServerNames) {

	if (ServerListScrollBox != nullptr) {

		ServerListScrollBox->ClearChildren();

		uint32 i = 0;

		for (const FString& Itr : ServerNames) {

			UPServerRow* TempServerRow = CreateWidget<UPServerRow>(this, ServerRowsClass);

			if (TempServerRow) {

				TempServerRow->ServerNameTextBox->SetText(FText::FromString(Itr));
				TempServerRow->Setup(this, i);
				++i;

				ServerListScrollBox->AddChild(TempServerRow);
			}
		}
	}
}