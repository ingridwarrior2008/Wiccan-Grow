// Fill out your copyright notice in the Description page of Project Settings.

#include "ExplosionActor.h"
#include "IDestructible.h"
#include "DestroyActorComponent.h"

AExplosionActor::AExplosionActor()
{
	PrimaryActorTick.bCanEverTick = true;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
    BoxComponent->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
//    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
//    RootComponent = StaticMeshComponent;
}

void AExplosionActor::BeginPlay()
{
	Super::BeginPlay();
	
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AExplosionActor::OnOlverlapStart);
}

void AExplosionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExplosionActor::OnOlverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor != nullptr &&
        OtherActor != this )
    {
        UActorComponent* ActorComponent = OtherActor->FindComponentByClass<UDestroyActorComponent>();
        UDestroyActorComponent* DestroyActorComponent = Cast<UDestroyActorComponent>(ActorComponent);
     
        IIDestructible* DestructibleObject = Cast<IIDestructible>(DestroyActorComponent);
        if (DestructibleObject)
        {
            DestructibleObject->DestroyObject();
        }
    }
}
