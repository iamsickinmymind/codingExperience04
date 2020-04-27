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

	ExitGameButton->OnClicked.AddDynamic(this, &UPMainMenu::OnExitGameClicked);

	HostGameButton->OnClicked.AddDynamic(this, &UPMainMenu::OnHostMenuClicked);
	JoinGameButton->OnClicked.AddDynamic(this, &UPMainMenu::OnJoinGameClicked);

	JoinServerButton->OnClicked.AddDynamic(this, &UPMainMenu::OnJoinServerClicked);
	CancelJoinButton->OnClicked.AddDynamic(this, &UPMainMenu::OnCancelJoinClicked);

	HostServerButton->OnClicked.AddDynamic(this, &UPMainMenu::OnHostGameClicked);
	CancelHostButton->OnClicked.AddDynamic(this, &UPMainMenu::OnCancelHostMenuClicked);

	return true;
}

void UPMainMenu::UpdateRows() {

	for (int32 i = 0; i < ServerListScrollBox->GetChildrenCount(); ++i) {

		UPServerRow* ChildRow = Cast<UPServerRow>(ServerListScrollBox->GetChildAt(i));

		if(ChildRow != nullptr) {

			ChildRow->bSelected = (SelectedIndex.IsSet() && i == SelectedIndex.GetValue());
		}
	}
}

void UPMainMenu::OnHostGameClicked() {

	if (MenuInterface) {

		if (CustomServerName->GetText().ToString().Len() > 0) {

			MenuInterface->HostServer(CustomServerName->GetText().ToString().ToUpper());
		}
	}
}

void UPMainMenu::OnHostMenuClicked() {

	if (MenuSwitcher && HostGameMenu) {

		MenuSwitcher->SetActiveWidget(HostGameMenu);
	}
	else return;
}

void UPMainMenu::OnCancelHostMenuClicked() {

	if (MenuSwitcher && MainMenu) {

		CustomServerName->SetText(FText::GetEmpty());
		MenuSwitcher->SetActiveWidget(MainMenu);
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

void UPMainMenu::SetServerList(TArray<FServerData> ServerData) {

	if (ServerListScrollBox != nullptr) {

		ServerListScrollBox->ClearChildren();

		uint32 i = 0;

		for (const FServerData& Itr : ServerData) {

			UPServerRow* TempServerRow = CreateWidget<UPServerRow>(this, ServerRowsClass);

			if (TempServerRow) {

					TempServerRow->ServerNameTextBox->SetText(FText::FromString(Itr.Name));
					TempServerRow->HostNameTextBlock->SetText(FText::FromString(Itr.HostUserName));
					TempServerRow->ConnectionFractionTextBlock->SetText(FText::FromString(FString::FromInt(Itr.CurrentPlayers).Append("/").Append(FString::FromInt(Itr.MaxPlayers))));
				TempServerRow->Setup(this, i);
				++i;

				ServerListScrollBox->AddChild(TempServerRow);
			}
		}
	}
}