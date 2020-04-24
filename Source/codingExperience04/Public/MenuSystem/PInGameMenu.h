// All rights reserved Dominik Pavlicek

#pragma once

#include "CoreMinimal.h"

#include "PMenuWidget.h"

#include "PInGameMenu.generated.h"

class UButton;

/**
 * (P)uzzle In Game Menu.
 */
UCLASS()
class CODINGEXPERIENCE04_API UPInGameMenu : public UPMenuWidget
{
	GENERATED_BODY()

protected:

	virtual bool Initialize() override;

	UFUNCTION()
	void OnResumeClicked();

	UFUNCTION()
	void OnQuitClicked();
	
protected:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ResumeGameButton = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* QuitGameButton = nullptr;
};
