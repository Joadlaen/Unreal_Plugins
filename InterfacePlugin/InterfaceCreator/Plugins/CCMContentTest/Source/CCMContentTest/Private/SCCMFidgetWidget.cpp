// Fill out your copyright notice in the Description page of Project Settings.


#include "SCCMFidgetWidget.h"
#include "SlateOptMacros.h"
#include "Kismet/GameplayStatics.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SCCMFidgetWidget::Construct(const FArguments& InArgs)
{
	
	
	ChildSlot
	[
		// Populate the widget
		SNew(SButton)
			.Text(FText::FromString("Scream"))
			.OnClicked(this, &SCCMFidgetWidget::ButtonPress)
	];
	
}

FReply SCCMFidgetWidget::ButtonPress()
{
	USoundBase* Sound = LoadObject<USoundBase>(nullptr, TEXT("/Script/Engine.SoundWave'/CCMContentTest/Myscream_1106_1153.Myscream_1106_1153'"));
	if (Sound)
	{
		UWorld* World = GEditor->GetEditorWorldContext().World();
		UGameplayStatics::PlaySound2D(World, Sound);
	}

	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
