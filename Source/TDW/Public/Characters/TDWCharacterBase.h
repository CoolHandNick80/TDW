// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "TDWCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayAbility;
class UMotionWarpingComponent;
class UNiagaraSystem;

UCLASS()
class TDW_API ATDWCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ATDWCharacterBase();

	/*AbilitySystemInterface*/
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	/*AbilitySystemInterface*/

	UAttributeSet* GetAttributeSet() { return AttributeSet; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetFacingTarget(const FVector& FacingTarget);
	virtual void SetFacingTarget_Implementation(const FVector& FacingTarget);

	UFUNCTION(BlueprintCallable)
	void SetLeapSlamData(const FVector& InTargetLocation);
	
	UFUNCTION(BlueprintCallable, NetMulticast, Unreliable)
	void Multicast_SpawnSystemAtLocation(const FVector& SpawnLocation, UNiagaraSystem* SystemTemplate);

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() {};

	void AddCharacterAbilities();

protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;

	TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent = nullptr;

	float ElapsedTime = 0;

	float HorizontalVelocity = 0.f;

	float VerticalVelocity = 0.f;

	float Duration = 0.f;

private:
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};
