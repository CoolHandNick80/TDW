// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/TDWAnimInstanceBase.h"
#include "Characters/TDWCharacterBase.h"

void UTDWAnimInstanceBase::NativeInitializeAnimation()
{
	OwnerCharacter = Cast<ATDWCharacterBase>(TryGetPawnOwner());
}

void UTDWAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!OwnerCharacter)
		return;

	CharacterSpeed = OwnerCharacter->GetVelocity().Size();
}
