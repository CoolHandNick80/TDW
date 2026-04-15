// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetControllers/OverlayWidgetController.h"
#include "AbilitySystem/TDWAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UTDWAttributeSet* TDWAttributeSet = CastChecked<UTDWAttributeSet>(AttributeSet.Get());

	OnHealthChanged.Broadcast(TDWAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(TDWAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(TDWAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(TDWAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UTDWAttributeSet* TDWAttributeSet = CastChecked<UTDWAttributeSet>(AttributeSet.Get());

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TDWAttributeSet->GetHealthAttribute()).AddLambda([&](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TDWAttributeSet->GetMaxHealthAttribute()).AddLambda([&](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TDWAttributeSet->GetManaAttribute()).AddLambda([&](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TDWAttributeSet->GetMaxManaAttribute()).AddLambda([&](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		});
}
