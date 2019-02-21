// Fill out your copyright notice in the Description page of Project Settings.

#include "PlantCreatorComponent.h"
#include "WiccanGrowGameInstance.h"

UPlantCreatorComponent::UPlantCreatorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlantCreatorComponent::BeginPlay()
{
	Super::BeginPlay();

    UWiccanGrowGameInstance* GameInstance = Cast<UWiccanGrowGameInstance>(GetWorld()->GetGameInstance());

    if (GameInstance)
    {
        bool bIsSpotLightActor = false;
        for (auto& Elem : GameInstance->SeedZoneActorsPosition)
        {
            switch (Elem.Key)
            {
                case ESeedType::ENone:
                {
                    break;
                }
                case ESeedType::EClimbingPlant:
                {
                    FVector TrunkLocation = FVector(Elem.Value.X, Elem.Value.Y, Elem.Value.Z - 100);
                    ATrunkActor* SpawnedActor = GetWorld()->SpawnActor<ATrunkActor>(TrunkActor, TrunkLocation, TrunkActorRotation);
                    
                    if(!bIsSpotLightActor)
                    {
                        SpawnedActor->SpotLightActor = SpotLightActor;
                        bIsSpotLightActor = true;
                    }
                    else
                    {
                        SpawnedActor->SpotLightActor = SpotLightActorBridge;
                    }
                    
                    SpawnedActor->SplineStaticMesh = SplineStaticMesh;
                    
                    SpawnedActor->LoadSplinePoints();
                    SpawnedActor->CreateSplineMesh();
                    
                    break;
                }
                case ESeedType::EBoomPlant:
                {
                    GetWorld()->SpawnActor<AActor>(BombPlant, Elem.Value, FRotator::ZeroRotator);
                    break;
                }
                case ESeedType::ELilyPadsPlant:
                {
                    GetWorld()->SpawnActor<AActor>(LilyPads, Elem.Value, FRotator::ZeroRotator);
                    break;
                }
            }
        }
    }
	
}

void UPlantCreatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

