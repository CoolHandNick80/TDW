// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TDWPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/TDWAbilitySystemComponent.h"
#include "Input/TDWInputComponent.h"

ATDWPlayerController::ATDWPlayerController()
{
	bReplicates = true;
}

void ATDWPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(TDWInputMappingContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem)
		Subsystem->AddMappingContext(TDWInputMappingContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void ATDWPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UTDWInputComponent* TDWInputComponent = Cast<UTDWInputComponent>(InputComponent);

	TDWInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATDWPlayerController::Move);
	TDWInputComponent->BindAbilityActions(InputConfig, this, &ATDWPlayerController::AbilityInputTagPressed, &ATDWPlayerController::AbilityInputTagReleased, &ATDWPlayerController::AbilityInputTagHeld);
}

void ATDWPlayerController::Move(const FInputActionValue& InputActionValue)
{
	if (!bCanMove)
		return;

	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void ATDWPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{

}

void ATDWPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetTDWAbilitySystemComponent())
		GetTDWAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
}

void ATDWPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetTDWAbilitySystemComponent())
		GetTDWAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
}

UTDWAbilitySystemComponent* ATDWPlayerController::GetTDWAbilitySystemComponent()
{
	if (TDWAbilitySystemComponent == nullptr)
	{
		TDWAbilitySystemComponent = Cast<UTDWAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}

	return TDWAbilitySystemComponent;
}
