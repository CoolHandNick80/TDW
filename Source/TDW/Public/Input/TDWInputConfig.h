// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "TDWInputConfig.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FTDWInputAction
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};


UCLASS()
class TDW_API UTDWInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;


public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FTDWInputAction> AbilityInputActions;
};
