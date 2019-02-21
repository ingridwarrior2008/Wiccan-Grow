// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DismissFloorActor.generated.h"

UCLASS()
class WICCANGOW_API ADismissFloorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADismissFloorActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
    
    UPROPERTY(EditAnywhere, Category = "Walls")
    AActor* Wall1;
    
    UPROPERTY(EditAnywhere, Category = "Walls")
    AActor* Wall2;
    
    UPROPERTY(EditAnywhere, Category = "Walls")
    AActor* Floor;
    
    UPROPERTY(EditAnywhere, Category = "Walls")
    FVector FloorLocation;
};
