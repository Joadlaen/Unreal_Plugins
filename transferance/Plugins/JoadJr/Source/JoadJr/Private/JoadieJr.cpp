// Fill out your copyright notice in the Description page of Project Settings.


#include "JoadieJr.h"

// Sets default values
AJoadieJr::AJoadieJr()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJoadieJr::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("jerry time"));
}

// Called every frame
void AJoadieJr::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

