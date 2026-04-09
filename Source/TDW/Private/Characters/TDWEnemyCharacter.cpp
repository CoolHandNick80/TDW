// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TDWEnemyCharacter.h"
#include "AbilitySystem/TDWAbilitySystemComponent.h"
#include "AbilitySystem/TDWAttributeSet.h"

ATDWEnemyCharacter::ATDWEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTDWAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UTDWAttributeSet>("AttributeSet");
}

void ATDWEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
}

void ATDWEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
