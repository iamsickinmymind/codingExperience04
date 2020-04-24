// All rights reserved Dominik Pavlicek

#include "PMenuWidget.h"

void UPMenuWidget::Setup() {

	this->AddToViewport();

	if (GetWorld()->GetFirstPlayerController()) {

		FInputModeUIOnly InputDataMode;
			InputDataMode.SetWidgetToFocus(this->TakeWidget());
			InputDataMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		GetWorld()->GetFirstPlayerController()->SetInputMode(InputDataMode);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	}
}

void UPMenuWidget::Remove() {

	this->RemoveFromViewport();

	if (GetWorld()->GetFirstPlayerController()) {

		

		FInputModeGameOnly InputDataMode;

		GetWorld()->GetFirstPlayerController()->SetInputMode(InputDataMode);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	}
}

void UPMenuWidget::SetMenuInterface(IMenuInterface* NewMenuInterface) {

	this->MenuInterface = NewMenuInterface;
}
