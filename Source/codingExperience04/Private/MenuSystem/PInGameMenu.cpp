// All rights reserved Dominik Pavlicek

#include "PInGameMenu.h"

#include "Components/Button.h"

bool UPInGameMenu::Initialize() {

	bool bSuccess = Super::Initialize();

	if (!bSuccess || !ResumeGameButton || !QuitGameButton) return bSuccess;

	ResumeGameButton->OnClicked.AddDynamic(this, &UPInGameMenu::OnResumeClicked);
	QuitGameButton->OnClicked.AddDynamic(this, &UPInGameMenu::OnQuitClicked);
	
	return true;
}

void UPInGameMenu::OnResumeClicked() {

	Remove();
}

void UPInGameMenu::OnQuitClicked() {

	if (MenuInterface) { 

		Remove();
		MenuInterface->ReloadMainMenu();
	}
}