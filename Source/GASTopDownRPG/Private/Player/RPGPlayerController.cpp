// Copyright ZJU doMGameMaker.


#include "Player/RPGPlayerController.h"
#include "EnhancedInputSubsystems.h"

ARPGPlayerController::ARPGPlayerController()
{
	bReplicates = true;

}

void ARPGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(PlayerContext);  // Halt execution if PlayerContext is not set

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(PlayerContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
}