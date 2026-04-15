// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TDWAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"

UTDWAttributeSet::UTDWAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitMana(100.f);
	InitMaxMana(100.f);
	InitAttackSpeed(10.f);
}

void UTDWAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME_CONDITION_NOTIFY(UTDWAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTDWAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTDWAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTDWAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTDWAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
}

void UTDWAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}

	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UTDWAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();

		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}

		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void UTDWAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{

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
