// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructiblePlantComponent.h"
#include "IDestructible.h"

UDestructiblePlantComponent::UDestructiblePlantComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
    
    if (GetOwner() != nullptr)
    {
        UActorComponent* ActorComponent = GetOwner()->GetComponentByClass(UBoxComponent::StaticClass());
        UBoxComponent* BoxComponent = Cast<UBoxComponent>(ActorComponent);
        
        if (BoxComponent)
        {
            BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &UDestructiblePlantComponent::OnOlverlapStart);
        }
    }
}


void UDestructiblePlantComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UDestructiblePlantComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDestructiblePlantComponent::OnOlverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    
    if ( (OtherActor != nullptr) &&
        (GetOwner() != nullptr) &&
        (OtherActor != GetOwner()) &&
        OverlappedComp != nullptr)
    {
        IIDestructible* DestructibleObject = Cast<IIDestructible>(OverlappedComp);
        if (DestructibleObject)
        {
            DestructibleObject->DestroyObject();
        }
    }
}
