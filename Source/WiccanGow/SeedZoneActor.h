// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Actor.h"
#include "SeedZoneActor.generated.h"

UENUM(BlueprintType, meta = (Bitflags))
enum class ESeedType : uint8
{
    ENone               UMETA(DisplayName = "None"),
    EClimbingPlant      UMETA(DisplayName = "ClimbingPlant"),
    EBoomPlant          UMETA(DisplayName = "BoomPlant"),
    ELilyPadsPlant      UMETA(DisplayName = "LilyPads")
};


UCLASS()
class WICCANGOW_API ASeedZoneActor : public AActor
{
	GENERATED_BODY()
	
public:
    
	ASeedZoneActor();
    
    void SetSeedSelection(ESeedType SeedType);
    ESeedType GetSeedSelection() const;
    
    bool ActorCanPutASeed() const;
    
    
    UFUNCTION()
    void OnSeedOlverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
    UFUNCTION()
    void OnSeedOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	virtual void BeginPlay() override;

public:
    
	virtual void Tick(float DeltaTime) override;

public:
    
    UPROPERTY(VisibleAnywhere, Category = "Seed Selection", meta=(Bitmask, BitmaskEnum = "ESeed type"))
    ESeedType SeedSelection;
    
    UPROPERTY(VisibleAnywhere, Category = "Box Collision")
    UBoxComponent* BoxComponent;
    
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent *StaticMeshComponent;
    
private:
    bool bCanPutASeed;
    
};
