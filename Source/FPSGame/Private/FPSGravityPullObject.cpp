// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGravityPullObject.h"
#include "Components/SphereComponent.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Actor.h>


// Sets default values
AFPSGravityPullObject::AFPSGravityPullObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComp->SetSimulatePhysics(true);
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(MeshComp);
	SphereComp->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AFPSGravityPullObject::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);


	for (int32 i = 0; i < FoundActors.Num(); i++) {

	/*	UE_LOG(LogClass, Log, TEXT("Name: %s"), *FoundActors[i]->GetName());*/

		if (*FoundActors[i]->GetName() == FString(TEXT("BP_BlackHole_2"))) {

			blackHole = FoundActors[i];

		}
	}

}

// Called every frame
void AFPSGravityPullObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// add gravity simulation
	if (blackHole != nullptr) {

		FVector directionVector = FVector(blackHole->GetActorLocation() - this->GetActorLocation());

		directionVector.Normalize();

		if (directionVector.IsNormalized()) {

			MeshComp->AddForce(directionVector * this->SCALAR_FORCE);
		}
	
	}
}

