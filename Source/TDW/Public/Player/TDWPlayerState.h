// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "TDWPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class TDW_API ATDWPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ATDWPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/*GameplayAbilityInterface*/
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	/*GameplayAbilityInterface*/

	UAttributeSet* GetAttributeSet() { return AttributeSet; }

	FORCEINLINE int32 GetCharacterLevel() const { return Level; }

private:
	UFUNCTION()
	virtual void OnRep_Level(int32 PreviousLevel);

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;

private:

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level)
	int32 Level = 1;
};
