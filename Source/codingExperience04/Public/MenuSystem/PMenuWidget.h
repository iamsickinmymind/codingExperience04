// All rights reserved Dominik Pavlicek

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "PMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class CODINGEXPERIENCE04_API UPMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void Setup();

	virtual void Remove();
	
	virtual void SetMenuInterface(IMenuInterface* MenuInterface);

protected:

	IMenuInterface* MenuInterface = nullptr;
};
