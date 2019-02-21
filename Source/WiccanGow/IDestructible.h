// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IDestructible.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIDestructible : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WICCANGOW_API IIDestructible
{
	GENERATED_BODY()

public:
    UFUNCTION()
    virtual void DestroyObject() = 0;
};
