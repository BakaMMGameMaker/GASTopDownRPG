// Copyright ZJU doMGameMaker.

#pragma once

#include "CoreMinimal.h"
#include "Character/RPGCharacterBase.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GASTOPDOWNRPG_API APlayerCharacter : public ARPGCharacterBase
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:
	void InitAbilityActorInfo();
};
