// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled((ECollisionEnabled::QueryOnly));
	OverlapComp->SetCollisionResponseToAllChannels((ECR_Ignore));
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.0f, 200.0f, 200.0f));
	OverlapComp->SetHiddenInGame(false);
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);
	RootComponent = OverlapComp;

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->DecalSize = FVector(200.0f);
	DecalComp->SetupAttachment(RootComponent);
}

void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent * OverlappedComponent, 
	AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult & SweepResult)
{
		UE_LOG(LogClass, Log, TEXT("Overlapped with extraction Zone: %s"));
}
