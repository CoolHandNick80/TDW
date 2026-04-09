// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TDWAnimInstanceBase.generated.h"

class ATDWCharacterBase;
/**
 * 
 */
UCLASS()
class TDW_API UTDWAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	ATDWCharacterBase* OwnerCharacter = nullptr;

	UPROPERTY(BlueprintReadOnly)
	float CharacterSpeed = 0.f;
};
