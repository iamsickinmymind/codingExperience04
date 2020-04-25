// All rights reserved Dominik Pavlicek

#include "PServerRow.h"

#include "Components/Button.h"

#include "PMainMenu.h"

void UPServerRow::Setup(class UPMainMenu* NewParent, uint32 NewIndex) {

	Parent = NewParent;
	Index = NewIndex;

	if (ServerRowButton != nullptr) {

		ServerRowButton->OnClicked.AddDynamic(this, &UPServerRow::OnRowClicked);
	}
}

void UPServerRow::OnRowClicked() {

	if(Parent != nullptr) {

		Parent->SetSelectedIndex(Index);
		Parent->UpdateRows();
	}
}
