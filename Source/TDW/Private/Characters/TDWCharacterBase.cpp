// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TDWCharacterBase.h"
#include "AbilitySystem/TDWAbilitySystemComponent.h"
#include "MotionWarpingComponent.h"
#include "AbilitySystem/TDWAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraFunctionLibrary.h"

ATDWCharacterBase::ATDWCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>("MotionWarpingComponent");
}

void ATDWCharacterBase::AddCharacterAbilities()
{
	UTDWAbilitySystemComponent* TDWAbilitySystemComponent = CastChecked<UTDWAbilitySystemComponent>(AbilitySystemComponent);

	if (!HasAuthority())
		return;

	TDWAbilitySystemComponent->AddCharacterAbilities(StartupAbilities);
}

void ATDWCharacterBase::SetFacingTarget_Implementation(const FVector& FacingTarget)
{
	MotionWarpingComponent->AddOrUpdateWarpTargetFromLocation("FacingTarget", FacingTarget);
}

void ATDWCharacterBase::SetLeapSlamData(const FVector& InTargetLocation)
{
	ElapsedTime = 0.f;
	
	float AttackSpeed = Cast<UTDWAttributeSet>(AttributeSet)->GetAttackSpeed();
	
	FVector StartLocation = GetActorLocation();
	StartLocation.Z = 0;

	FVector TargetLocation = InTargetLocation;
	TargetLocation.Z = 0;

	float TargetDistance = FVector::Dist(StartLocation, TargetLocation);

	HorizontalVelocity = AttackSpeed * 40.f;

	Duration = TargetDistance / HorizontalVelocity;

	float HeightDelta = InTargetLocation.Z - (GetActorLocation().Z - GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight());

	VerticalVelocity = (-1.F * GetCharacterMovement()->GetGravityZ() * Duration) / 2 + HeightDelta / Duration;

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

	SetActorTickEnabled(true);
}

void ATDWCharacterBase::Multicast_SpawnSystemAtLocation_Implementation(const FVector& SpawnLocation, UNiagaraSystem* SystemTemplate)
{
	if(HasAuthority() || !IsLocallyControlled())
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, SystemTemplate, SpawnLocation);
}

void ATDWCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

UAbilitySystemComponent* ATDWCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
