// Fill out your copyright notice in the Description page of Project Settings.

#include "DismissFloorActor.h"

// Sets default values
ADismissFloorActor::ADismissFloorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADismissFloorActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADismissFloorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (Wall1->bHidden && Wall2->bHidden)
    {
        Floor->SetActorLocation(FloorLocation);
    }
}

