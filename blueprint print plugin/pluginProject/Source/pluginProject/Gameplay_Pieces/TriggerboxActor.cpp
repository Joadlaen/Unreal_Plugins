// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay_Pieces/TriggerboxActor.h"

// Sets default values
ATriggerboxActor::ATriggerboxActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATriggerboxActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATriggerboxActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

