// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProofOfLife.generated.h"

UCLASS()
class FPHYS_API AProofOfLife : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProofOfLife();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
