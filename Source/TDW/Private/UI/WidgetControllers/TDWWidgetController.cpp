// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetControllers/TDWWidgetController.h"

void UTDWWidgetController::SetWidgetControllerParams(const FWidgetControllerParams WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UTDWWidgetController::BroadcastInitialValues()
{
}

void UTDWWidgetController::BindCallbacksToDependencies()
{
}
