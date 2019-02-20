// Fill out your copyright notice in the Description page of Project Settings.

#include "InputHandlerActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInputHandlerActor::AInputHandlerActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AInputHandlerActor::BeginPlay()
{
	Super::BeginPlay();
	
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    
    if (PlayerController)
    {
        EnableInput(PlayerController);
        
        InputComponent->BindAction("PlantClimbing", EInputEvent::IE_Pressed, this, &AInputHandlerActor::PlantClimbing);
        InputComponent->BindAction("PlantBoom", EInputEvent::IE_Pressed, this, &AInputHandlerActor::PlantBoom);
        InputComponent->BindAction("PlantLilyPads", EInputEvent::IE_Pressed, this, &AInputHandlerActor::PlantLilyPads);
    }
}

void AInputHandlerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInputHandlerActor::PlantClimbing()
{
    PlantSeedWithType(ESeedType::EClimbingPlant);
}

void AInputHandlerActor::PlantBoom()
{
    PlantSeedWithType(ESeedType::EBoomPlant);
}

void AInputHandlerActor::PlantLilyPads()
{
    PlantSeedWithType(ESeedType::ELilyPadsPlant);
}

void AInputHandlerActor::PlantSeedWithType(ESeedType SeedType)
{
    TArray<AActor*> SeedZoneActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASeedZoneActor::StaticClass(), SeedZoneActors);
    
    //TODO: Refactor this
    for (AActor* Actor : SeedZoneActors)
    {
        ASeedZoneActor* SeedActor = Cast<ASeedZoneActor>(Actor);
        if (SeedActor->ActorCanPutASeed())
        {
            SeedActor->SetSeedSelection(SeedType);
        }
    }
}
