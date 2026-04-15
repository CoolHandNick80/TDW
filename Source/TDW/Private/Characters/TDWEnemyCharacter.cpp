// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TDWEnemyCharacter.h"
#include "AbilitySystem/TDWAbilitySystemComponent.h"
#include "AbilitySystem/TDWAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "UI/Widgets/TDWUserWidget.h"

ATDWEnemyCharacter::ATDWEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTDWAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UTDWAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(RootComponent);
}

void ATDWEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();

	if (UTDWUserWidget* TDWUserWidget = Cast<UTDWUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		TDWUserWidget->SetWidgetController(this);
	}

	if (UTDWAttributeSet* TDWAtributeSet = Cast<UTDWAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TDWAtributeSet->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			});

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TDWAtributeSet->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			});

		OnHealthChanged.Broadcast(TDWAtributeSet->GetHealth());
		OnMaxHealthChanged.Broadcast(TDWAtributeSet->GetMaxHealth());
	}
}

void ATDWEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
