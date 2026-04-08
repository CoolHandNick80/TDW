// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TDWPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

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

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> TDWInputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
};
