// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include <Kismet/GameplayStatics.h>

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn * InstigatorPawn)
{
	if (InstigatorPawn) {

		InstigatorPawn->DisableInput(nullptr);

		if (SpectatingViewPointClass) {

			TArray<AActor*> returnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewPointClass, returnedActors);

			if (returnedActors.Num() > 0) {

				AActor* newViewTarget = returnedActors[0];

				APlayerController * playerController = Cast<APlayerController>(InstigatorPawn->GetController());
				if (playerController) {
					playerController->SetViewTargetWithBlend(newViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		}

	
	}

	OnMissionCompleted(InstigatorPawn);
}
