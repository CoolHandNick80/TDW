// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TDWCharacterBase.h"

ATDWCharacterBase::ATDWCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATDWCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

UAbilitySystemComponent* ATDWCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
