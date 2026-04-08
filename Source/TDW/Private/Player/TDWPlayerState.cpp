// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TDWPlayerState.h"
#include "AbilitySystem/TDWAbilitySystemComponent.h"
#include "AbilitySystem/TDWAttributeSet.h"
#include "Net/UnrealNetwork.h"

ATDWPlayerState::ATDWPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTDWAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UTDWAttributeSet>("AttributeSet");

	SetNetUpdateFrequency(100.f);
}

void ATDWPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATDWPlayerState, Level);
}

UAbilitySystemComponent* ATDWPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATDWPlayerState::OnRep_Level(int32 PreviousLevel)
{
}
