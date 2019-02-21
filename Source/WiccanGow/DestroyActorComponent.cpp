// Fill out your copyright notice in the Description page of Project Settings.

#include "DestroyActorComponent.h"

// Sets default values for this component's properties
UDestroyActorComponent::UDestroyActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDestroyActorComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UDestroyActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDestroyActorComponent::DestroyObject()
{
    if (bShowWaterAfterDestroy)
    {
        GetWorld()->SpawnActor<AActor>(WaterActor, WaterLocation, FRotator::ZeroRotator);
    }
    
    GetOwner()->SetActorHiddenInGame(true);
}
