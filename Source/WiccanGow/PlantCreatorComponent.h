// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrunkActor.h"
#include "Components/ActorComponent.h"
#include "PlantCreatorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WICCANGOW_API UPlantCreatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlantCreatorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
    
    UPROPERTY(EditAnywhere, Category = "Spawning Seeds")
    TSubclassOf<class ATrunkActor> TrunkActor;
    
    UPROPERTY(EditAnywhere, Category = "Spawning Seeds")
    TSubclassOf<AActor> BombPlant;
    
    UPROPERTY(EditAnywhere, Category = "Spawning Seeds")
    TSubclassOf<AActor> LilyPads;
    
    UPROPERTY(EditAnywhere, Category = "Spawning Seeds")
    ASpotLight* SpotLightActor;
    
    UPROPERTY(EditAnywhere, Category = "Spawning Seeds")
    ASpotLight* SpotLightActorBridge;
    
    UPROPERTY(EditAnywhere, Category = "Spawning Seeds")
    UStaticMesh* SplineStaticMesh;
    
    UPROPERTY(EditAnywhere, Category = "Spawning Seeds")
    FRotator TrunkActorRotation;
};
