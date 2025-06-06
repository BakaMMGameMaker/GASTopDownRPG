// Copyright ZJU doMGameMaker.


#include "UI/HUD/RPGHUD.h"

#include "UI/Widget/RPGUserWidget.h"

void ARPGHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
