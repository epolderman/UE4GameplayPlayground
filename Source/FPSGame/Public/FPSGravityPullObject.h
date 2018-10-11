// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSGravityPullObject.generated.h"

class USphereComponent;

UCLASS()
class FPSGAME_API AFPSGravityPullObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSGravityPullObject();

	// Visually show objective
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent * MeshComp;

	// Collision info
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;

	AActor * blackHole;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
