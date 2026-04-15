// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/TDWCharacterBase.h"
#include "UI/WidgetControllers/OverlayWidgetController.h"
#include "TDWEnemyCharacter.generated.h"

class UWidgetComponent;

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

public:

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
};
