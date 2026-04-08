// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TDWAttributeSet.h"
#include "Net/UnrealNetwork.h"

UTDWAttributeSet::UTDWAttributeSet()
{
}

void UTDWAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME_CONDITION_NOTIFY(UTDWAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTDWAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTDWAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTDWAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTDWAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
}

void UTDWAttributeSet::OnRep_Health(const FGameplayAttributeData& PreviousHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTDWAttributeSet, Health, PreviousHealth);
}

void UTDWAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& PreviousMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTDWAttributeSet, MaxHealth, PreviousMaxHealth);
}

void UTDWAttributeSet::OnRep_Mana(const FGameplayAttributeData& PreviousMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTDWAttributeSet, Mana, PreviousMana);
}

void UTDWAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& PreviousMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTDWAttributeSet, MaxMana, PreviousMaxMana);
}

void UTDWAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& PreviousAttackSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTDWAttributeSet, AttackSpeed, PreviousAttackSpeed);
}
