// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TDWPlayerCharacter.h"
#include "Player/TDWPlayerState.h"
#include "Player/TDWPlayerController.h"
#include "AbilitySystem/TDWAbilitySystemComponent.h"
#include "AbilitySystem/TDWAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTagContainer.h"
#include "UI/HUD/TDWHUD.h"

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

	AddCharacterAbilities();
}

void ATDWPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

void ATDWPlayerCharacter::Tick(float DeltaTime)
{
	ElapsedTime += DeltaTime;
	
	if (ElapsedTime >= Duration)
	{
		SetActorTickEnabled(false);

		GetCharacterMovement()->Velocity = FVector::ZeroVector;
		FGameplayTag EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Montage.JumpEnd"));
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, EventTag, FGameplayEventData());
	}
	else
	{
		FVector Vector = GetActorForwardVector() * HorizontalVelocity;
		Vector.Z = VerticalVelocity + GetCharacterMovement()->GetGravityZ() * ElapsedTime;

		GetCharacterMovement()->Velocity = Vector;
		//AddMovementInput(Vector);
	}
}

void ATDWPlayerCharacter::InitAbilityActorInfo()
{
	ATDWPlayerState* TDWPlayerState = GetPlayerState<ATDWPlayerState>();
	check(TDWPlayerState);
	TDWPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(TDWPlayerState, this);
	AbilitySystemComponent = TDWPlayerState->GetAbilitySystemComponent();
	AttributeSet = TDWPlayerState->GetAttributeSet();

	if (ATDWPlayerController* TDWPlayerController = Cast<ATDWPlayerController>(GetController()))
	{
		if (ATDWHUD* TDWHUD = Cast<ATDWHUD>(TDWPlayerController->GetHUD()))
		{
			TDWHUD->InitOverlay(TDWPlayerController, TDWPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}
