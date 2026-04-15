// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/TDWUserWidget.h"

void UTDWUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
