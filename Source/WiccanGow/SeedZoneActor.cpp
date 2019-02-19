// Fill out your copyright notice in the Description page of Project Settings.

#include "SeedZoneActor.h"

ASeedZoneActor::ASeedZoneActor()
{
	PrimaryActorTick.bCanEverTick = true;
    
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    RootComponent = StaticMeshComponent;
    
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASeedZoneActor::OnSeedOlverlap);
}

void ASeedZoneActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASeedZoneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASeedZoneActor::OnSeedOlverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if ( (OtherActor != nullptr ) && (OtherActor != this) && ( OtherComp != nullptr ) )
    {
        SeedSelection = ESeedType::EClimbingPlant;
    }
}
