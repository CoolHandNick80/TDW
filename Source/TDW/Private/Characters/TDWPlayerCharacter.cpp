// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TDWPlayerCharacter.h"
#include "Player/TDWPlayerState.h"
#include "Player/TDWPlayerController.h"
#include "AbilitySystem/TDWAbilitySystemComponent.h"
#include "AbilitySystem/TDWAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"

ATDWPlayerCharacter::ATDWPlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);

	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->bInheritYaw = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	CharacterMovementComponent = GetCharacterMovement();
	ensure(CharacterMovementComponent);

	CharacterMovementComponent->bOrientRotationToMovement = true;
	CharacterMovementComponent->RotationRate = FRotator(0.f, 400.f, 0.f);
	CharacterMovementComponent->bConstrainToPlane = true;
	CharacterMovementComponent->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void ATDWPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server
	InitAbilityActorInfo();
}

void ATDWPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

void ATDWPlayerCharacter::InitAbilityActorInfo()
{
	ATDWPlayerState* TDWPlayerState = GetPlayerState<ATDWPlayerState>();
	check(TDWPlayerState);
	TDWPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(TDWPlayerState, this);
	AbilitySystemComponent = TDWPlayerState->GetAbilitySystemComponent();
	AttributeSet = TDWPlayerState->GetAttributeSet();
}
