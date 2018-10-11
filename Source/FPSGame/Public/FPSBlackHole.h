// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBlackHole.generated.h"

class USphereComponent;

UCLASS()
class FPSGAME_API AFPSBlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSBlackHole();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Visually show objective
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent * MeshComp;

	// Collision info
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* SphereComp;
public:	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
