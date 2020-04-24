// All rights reserved Dominik Pavlicek

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class CODINGEXPERIENCE04_API IMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// pure fce
	// actual logic will be implemented in child class
	virtual void HostServer() = 0;
	virtual void JoinServer(const uint32 SessionIndex ) = 0;

	virtual void ReloadMainMenu() = 0;
	virtual void ExitGame_Desktop() = 0;

	virtual void RefreshServerList() = 0;
};
