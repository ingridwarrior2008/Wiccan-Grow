// Fill out your copyright notice in the Description page of Project Settings.

#include "SeedZoneActor.h"
#include "WiccanGrowGameInstance.h"

ASeedZoneActor::ASeedZoneActor()
{
    PrimaryActorTick.bCanEverTick = true;
    
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    RootComponent = StaticMeshComponent;
    bCanPutASeed = false;
    SeedSelection = ESeedType::EClimbingPlant;
}

void ASeedZoneActor::BeginPlay()
{
    Super::BeginPlay();
    
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASeedZoneActor::OnSeedOlverlapStart);
    BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ASeedZoneActor::OnSeedOverlapEnd);
}

void ASeedZoneActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASeedZoneActor::OnSeedOlverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if ( (OtherActor != nullptr ) && (OtherActor != this) && (OtherActor->Tags.Contains("Player")))
    {
        bCanPutASeed = true;
    }
}

void ASeedZoneActor::OnSeedOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    bCanPutASeed = false;
}

void ASeedZoneActor::SetSeedSelection(ESeedType SeedType)
{
    SeedSelection = SeedType;
    UWiccanGrowGameInstance* GameInstance = Cast<UWiccanGrowGameInstance>(GetWorld()->GetGameInstance());
    
    bool bIsSeedSpawned = false;
   
    //TODO: Refactor this ->
    for (auto& Elem : GameInstance->SeedZoneActorsPosition)
    {
        if (Elem.Value == this->GetActorLocation())
        {
            bIsSeedSpawned = true;
        }
    }
    
    //TODO: Update the saved value on the array
    if (!bIsSeedSpawned)
    {
        GameInstance->SeedZoneActorsPosition.Add(SeedSelection, GetActorLocation());
    }
}

ESeedType ASeedZoneActor::GetSeedSelection() const
{
    return SeedSelection;
}

bool ASeedZoneActor::ActorCanPutASeed() const
{
    return bCanPutASeed;
}
