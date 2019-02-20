// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IDestructible.h"
#include "DestroyActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WICCANGOW_API UDestroyActorComponent : public UActorComponent, public IIDestructible
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDestroyActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
    virtual void DestroyObject() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:
    UPROPERTY(EditAnywhere, Category = "Destroy config")
    bool bShowWaterAfterDestroy;
    
    UPROPERTY(EditAnywhere, Category = "Destroy config")
    TSubclassOf<AActor> WaterActor;
    
    UPROPERTY(EditAnywhere, Category = "Destroy config")
    FVector WaterLocation;
};
