// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "TDWPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UTDWInputConfig;
class UTDWAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class TDW_API ATDWPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATDWPlayerController();

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:
	void Move(const FInputActionValue& InputActionValue);

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UTDWAbilitySystemComponent* GetTDWAbilitySystemComponent();
public:
	UPROPERTY(BlueprintReadWrite)
	bool bCanMove = true;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> TDWInputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UTDWInputConfig> InputConfig;

	TObjectPtr<UTDWAbilitySystemComponent> TDWAbilitySystemComponent;

};
