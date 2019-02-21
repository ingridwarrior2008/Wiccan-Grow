// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SeedZoneActor.h"
#include "SeedContainerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WICCANGOW_API USeedContainerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
    
	USeedContainerComponent();

protected:

	virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    
public:
    
    UPROPERTY(EditAnywhere, Category = "Seed Classes")
    TArray<AActor*> SeedZoneActors;
		
};
