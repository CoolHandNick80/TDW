// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/TDWCharacterBase.h"
#include "TDWEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TDW_API ATDWEnemyCharacter : public ATDWCharacterBase
{
	GENERATED_BODY()

public:
	ATDWEnemyCharacter();
	
protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

};
