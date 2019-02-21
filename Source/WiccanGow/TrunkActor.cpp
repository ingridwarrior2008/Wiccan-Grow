// Fill out your copyright notice in the Description page of Project Settings.

#include "TrunkActor.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"

#pragma mark - Constructor

ATrunkActor::ATrunkActor()
{
	PrimaryActorTick.bCanEverTick = true;

    TruckLine = CreateDefaultSubobject<USplineComponent>(FName("TruckLine"));
    TruckLine->SetupAttachment(RootComponent);
}

#pragma mark - LifeCycle

void ATrunkActor::BeginPlay()
{
	Super::BeginPlay();
    
    LoadSplinePoints();
    CreateSplineMesh();
}


void ATrunkActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    HandleRayCasting();
}

#pragma mark - Protected Methods

void ATrunkActor::OnConstruction(const FTransform& Transform)
{
    if (bEditSplineLineOnEditMode)
    {
        CreateSplineMesh();
    }
}

void ATrunkActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    if (PropertyChangedEvent.Property != NULL &&
        (PropertyChangedEvent.Property->GetFName() == FName(TEXT("NumberOfSplinePoints"))))
    {
        TruckLine->ClearSplinePoints();
        LoadSplinePoints();
        
        ReloadSplineMesh();
    }
    
    Super::PostEditChangeProperty(PropertyChangedEvent);
}


#pragma mark - Private Methods

void ATrunkActor::HandleRayCasting()
{
    FHitResult OutHit;
    
    if (SpotLightActor == nullptr)
    {
        return;
    }
    
    FVector Start = SpotLightActor->GetActorLocation();
    
    FVector ForwardVector = SpotLightActor->GetActorForwardVector();
    FVector End = ((ForwardVector * 1000.f) + Start);
    FCollisionQueryParams CollisionParams;
    
    DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);
    
    if(GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams))
    {
        UPrimitiveComponent* HitPrimitiveLocation = OutHit.GetComponent();
        USplineMeshComponent* SplineMeshComponent = Cast<USplineMeshComponent>(HitPrimitiveLocation);
        
        if (SplineMeshComponent)
        {
            int OutIndex;
            
            if (SplineMeshComponents.Find(SplineMeshComponent, OutIndex))
            {
                //TODO: Consider to refactor this ->
                int positionDistance = YCurveDistancePoints;
                
                int LastPointX;
                bool bCalculateCurve = false;
                
                if (!bIsRayCastingDisplaying)
                {
                    for (int32 i = OutIndex; i < TruckLine->GetNumberOfSplinePoints(); i++)
                    {
                        FVector lastPoint = TruckLine->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Type::Local);
                        
                        if (i == OutIndex)
                        {
                            LastPointX = lastPoint.X;
                        }
                        else if (i > OutIndex && i < TruckLine->GetNumberOfSplinePoints() && !bCalculateCurve)
                        {
                            LastPointX = LastPointX + MaxCurveHeightDistance;
                            bCalculateCurve = true;
                        }
                        
                        FVector UpdatedVector = FVector(LastPointX, positionDistance, 0.0f);
                        positionDistance+= YCurveDistancePoints;
                        
                        TruckLine->SetLocationAtSplinePoint(i, UpdatedVector, ESplineCoordinateSpace::Type::Local, true);
                    }
                    
                    bIsRayCastingDisplaying = true;
                    ReloadSplineMesh();
                }
            }
        }
    }
}


void ATrunkActor::ReloadSplineMesh()
{
    //TODO: this is a workaround to dynamically show the spline meshes, don't ask me why! it's unreal fucking bug!
    FTimerHandle timer;
    GetWorldTimerManager().SetTimer(timer, this, &ATrunkActor::CreateSplineMesh, CreateSplineMeshDelay);
}

void ATrunkActor::ClearUSplineMeshComponents()
{
    if (SplineMeshComponents.Num() > 0)
    {
        for (int32 i = 0; i < SplineMeshComponents.Num(); i++)
        {
            if (SplineMeshComponents[i])
            {
                SplineMeshComponents[i]->DetachFromParent();
                SplineMeshComponents[i]->DestroyComponent();
            }
        }
        SplineMeshComponents.Empty();
    }
}

#pragma mark - Public Methods

void ATrunkActor::LoadSplinePoints()
{
    if (TruckLine)
    {
        TArray <FVector> Points;
        
        int32 CurrentPoint = StartPoint;
        
        for (int32 i = 0; i < NumberOfSplinePoints; i++)
        {
            FVector Point = FVector(CurrentPoint, 0.0f, 0.0f);
            Points.Add(Point);
            CurrentPoint += ZDistanceBetweenPoints;
        }
        
        TruckLine->SetSplinePoints(Points, ESplineCoordinateSpace::Type::Local, true);
    }
}

void ATrunkActor::CreateSplineMesh()
{
    FVector LocStart, TanStart, LocEnd, TanEnd;
    
    ClearUSplineMeshComponents();
    
    int32 NumberOfPoints = TruckLine->GetNumberOfSplinePoints();
    
    if (NumberOfPoints < 2)
    {
        UE_LOG(LogTemp, Display, TEXT("Can't create the spline mesh, need more points"));
        return;
    }
    
    for (int32 i = 0; i < (NumberOfPoints - 1); i++)
    {
        USplineMeshComponent* SplineMeshComponent = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
        SplineMeshComponent->RegisterComponent();
        SplineMeshComponent->CreationMethod = EComponentCreationMethod::UserConstructionScript;
        
        TruckLine->GetLocationAndTangentAtSplinePoint(i, LocStart, TanStart, ESplineCoordinateSpace::Local);
        TruckLine->GetLocationAndTangentAtSplinePoint(i + 1, LocEnd, TanEnd, ESplineCoordinateSpace::Local);
        
        SplineMeshComponent->SetStartScale(FVector2D(SplineLineScale, SplineLineScale));
        SplineMeshComponent->SetEndScale(FVector2D(SplineLineScale, SplineLineScale));
        
        SplineMeshComponent->SetMobility(EComponentMobility::Type::Movable);
        SplineMeshComponent->SetForwardAxis(ESplineMeshAxis::X);
        
        SplineMeshComponent->SetStaticMesh(SplineStaticMesh);
        
        SplineMeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
        SplineMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        SplineMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
        SplineMeshComponent->SetStartAndEnd(LocStart, TanStart, LocEnd, TanEnd);
        SplineMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
        
        SplineMeshComponents.Add(SplineMeshComponent);
    }
}
