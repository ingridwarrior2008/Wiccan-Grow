// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/SpotLight.h"
#include "TrunkActor.generated.h"

UCLASS()
class WICCANGOW_API ATrunkActor : public AActor
{
	GENERATED_BODY()
	
public:
	ATrunkActor();

protected:

	virtual void BeginPlay() override;
    
    virtual void OnConstruction(const FTransform &Transform) override;
    
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;


public:
	virtual void Tick(float DeltaTime) override;
    void CreateSplineMesh();
    void LoadSplinePoints();
    
public:
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spline")
    USplineComponent* TruckLine;
    
    UPROPERTY(EditAnywhere, Category = "SplineLine Mesh")
    UStaticMesh* SplineStaticMesh;
    
    UPROPERTY(EditAnywhere, Category = "SplineLine Mesh")
    bool bEditSplineLineOnEditMode;
    
    UPROPERTY(EditAnywhere, Category = "SplineLine Mesh")
    int32 NumberOfSplinePoints = 5;
    
    UPROPERTY(EditAnywhere, Category = "SplineLine Mesh")
    int32 ZDistanceBetweenPoints = 100;
    
    UPROPERTY(EditAnywhere, Category = "SplineLine Mesh")
    int32 YCurveDistancePoints = 200;
    
    UPROPERTY(EditAnywhere, Category = "SplineLine Mesh")
    int32 MaxCurveHeightDistance = 50;
    
    UPROPERTY(EditAnywhere, Category = "SplineLine Mesh")
    float SplineLineScale = 1;
    
    UPROPERTY(VisibleAnywhere, Category = "SplineLine Mesh")
    TArray<USplineMeshComponent*> SplineMeshComponents;
    
    UPROPERTY(EditAnywhere, Category = "SplineLine Mesh")
    ASpotLight* SpotLightActor;
    
    const int32 StartPoint = 100.0f;
    const float CreateSplineMeshDelay = 0.2f;
  
    int CurrentRayCastIndex;
    
    bool bIsRayCastingDisplaying = false;
    
private:
    
    void HandleRayCasting();
    void ReloadSplineMesh();
    void ClearUSplineMeshComponents();
};
