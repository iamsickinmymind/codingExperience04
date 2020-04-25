// All rights reserved Dominik Pavlicek

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PServerRow.generated.h"

class UButton;
class UPMainMenu;
class UTextBlock;

/**
 * (P)uzzle Server Row
 */
UCLASS()
class CODINGEXPERIENCE04_API UPServerRow : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ServerNameTextBox = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* HostNameTextBlock = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ConnectionFractionTextBlock = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ServerRowButton = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	bool bSelected;

protected:

	uint32 Index;

	UPROPERTY()
	UPMainMenu* Parent = nullptr;

public:

	void Setup(UPMainMenu* NewParent, uint32 NewIndex);
	
protected:

	UFUNCTION()
	void OnRowClicked();
	
};
