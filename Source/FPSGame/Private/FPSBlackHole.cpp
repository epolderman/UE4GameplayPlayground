// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSBlackHole.h"
#include "Components/SphereComponent.h"
#include <Engine/Engine.h>
#include "FPSGravityPullObject.h"
#include "FPSCharacter.h"


// Sets default values
AFPSBlackHole::AFPSBlackHole()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void AFPSBlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSBlackHole::NotifyActorBeginOverlap(AActor * OtherActor)
{
	UE_LOG(LogClass, Log, TEXT("NotifyActorBeginOverlap BLACKHOLE!"));

	Super::NotifyActorBeginOverlap(OtherActor);

	AFPSGravityPullObject * MyCharacter = Cast<AFPSGravityPullObject>(OtherActor);

	if (MyCharacter != nullptr) {

		UE_LOG(LogClass, Log, TEXT("Destroying...!: %s"), *MyCharacter->GetName());
		MyCharacter->Destroy();
	}
}

