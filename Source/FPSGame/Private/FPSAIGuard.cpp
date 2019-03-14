// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include <GameFramework/Actor.h>
#include "FPSGameMode.h"
#include <EngineUtils.h>
#include <Engine/StaticMeshActor.h>


// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);

	OriginalRotation = GetActorRotation();

	GuardState = EAIState::Idle;
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	
	// grab target action points
	// use the navigation mesh to patrol character
}

void AFPSAIGuard::OnPawnSeen(APawn * SeenPawn)
{
	if (SeenPawn != nullptr) {
		UE_LOG(LogClass, Log, TEXT("Seen Pawn"));
		SetGuardState(EAIState::Alerted);
		DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);
		AFPSGameMode * gameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
		if (gameMode)
			gameMode->CompleteMission(SeenPawn, false);
	}
}

void AFPSAIGuard::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	// Location = unit vector 
	// pitch is up y
	// roll is x axis
	// yaw is z axis

	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 10.0f);

	if (GuardState == EAIState::Alerted) {
		return;
	}

	SetGuardState(EAIState::Suspicious);
	FVector locationofNoise = Location - GetActorLocation();
	locationofNoise.Normalize();
	FRotator lookAtVector = FRotationMatrix::MakeFromX(locationofNoise).Rotator();
	lookAtVector.Pitch = 0.0f;
	lookAtVector.Roll = 0.0f;
	SetActorRotation(lookAtVector);


	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AFPSAIGuard::resetOrientation, 3.0f);
}


void AFPSAIGuard::resetOrientation()
{
	if (GuardState == EAIState::Alerted)
	return;

	SetActorRotation(OriginalRotation);
	SetGuardState(EAIState::Idle);
}

void AFPSAIGuard::SetGuardState(EAIState NewState)
{
	if (GuardState == NewState)
	return;

	GuardState = NewState;
	OnStateChanged(GuardState);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

