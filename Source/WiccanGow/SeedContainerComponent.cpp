// Fill out your copyright notice in the Description page of Project Settings.

#include "SeedContainerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WiccanGrowGameInstance.h"

USeedContainerComponent::USeedContainerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USeedContainerComponent::BeginPlay()
{
	Super::BeginPlay();
    
}

void USeedContainerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    
    if (EndPlayReason == EEndPlayReason::LevelTransition)
    {
        /*UWiccanGrowGameInstance* GameInstance = Cast<UWiccanGrowGameInstance>(GetWorld()->GetGameInstance());

        if (GameInstance)
        {
            for (AActor* Actor : SeedZoneActors)
            {
                ASeedZoneActor* SeedActor = Cast<ASeedZoneActor>(Actor);
                //UE_LOG(LogTemp, Display, TEXT("%d"), SeedActor->GetSeedSelection());
                GameInstance->SeedZoneActors.Add(SeedActor);
            }
        }*/
    }
}

void USeedContainerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    //UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASeedZoneActor::StaticClass(), SeedZoneActors);
}

