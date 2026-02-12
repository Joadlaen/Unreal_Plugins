// Fill out your copyright notice in the Description page of Project Settings.


#include "ProofOfLife.h"
#include "Engine.h"

// Sets default values
AProofOfLife::AProofOfLife()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProofOfLife::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Plugin is active"));	
	
}

// Called every frame
void AProofOfLife::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

