// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SeedZoneActor.h"
#include "WiccanGrowGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class WICCANGOW_API UWiccanGrowGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
    TMultiMap<ESeedType, FVector> SeedZoneActorsPosition;
};
