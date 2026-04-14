// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/TDWCharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TDWPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TDW_API ATDWPlayerCharacter : public ATDWCharacterBase
{
	GENERATED_BODY()
	
public:
	ATDWPlayerCharacter();

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

protected:
	virtual void Tick(float DeltaTime) override;

private:
	virtual void InitAbilityActorInfo() override;

protected:

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY()
	UCharacterMovementComponent* CharacterMovementComponent = nullptr;
};
