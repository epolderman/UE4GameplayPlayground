// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"


// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSAIGuard::OnPawnSeen(APawn * SeenPawn)
{
	if (SeenPawn != nullptr) {
		UE_LOG(LogClass, Log, TEXT("Seen Pawn"));
		DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);
	}
}

void AFPSAIGuard::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	// Location = unit vector 
	// pitch is up y
	// roll is x axis
	// yaw is z axis

	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 10.0f);

	FVector locationofNoise = Location - GetActorLocation();
	locationofNoise.Normalize();

	FRotator lookAtVector = FRotationMatrix::MakeFromX(locationofNoise).Rotator();
	lookAtVector.Pitch = 0.0f;
	lookAtVector.Roll = 0.0f;

	SetActorRotation(lookAtVector);
}


// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

