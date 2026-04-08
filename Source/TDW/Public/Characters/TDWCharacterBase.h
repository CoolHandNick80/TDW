// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "TDWCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class TDW_API ATDWCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ATDWCharacterBase();

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() {};

	/*AbilitySystemInterface*/
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	/*AbilitySystemInterface*/

	UAttributeSet* GetAttributeSet() { return AttributeSet; }

protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;

};
