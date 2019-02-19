// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
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
	// Sets default values for this actor's properties
	ASeedZoneActor();
    
    void SetSeedSelection(ESeedType SeedType);
    ESeedType GetSeedSelection() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
    void OnSeedOlverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
    
    UPROPERTY(VisibleAnywhere, Category = "Seed Selection", meta=(Bitmask, BitmaskEnum = "ESeed type"))
    ESeedType SeedSelection;
    
    UPROPERTY(VisibleAnywhere, Category = "Box Collision")
    UBoxComponent* BoxComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent *StaticMeshComponent;
};
