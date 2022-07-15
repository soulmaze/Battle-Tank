// Fill out your copyright notice in the Description page of Project Settings.

#include "TankRecreat.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

    auto ControlledTank = GetTankController();
    if(!ControlledTank)
    {
	    UE_LOG(LogTemp, Warning,TEXT("playercontroller not possessing a tank"));
    }
    else
    {
	    UE_LOG(LogTemp, Warning,TEXT("playercontroller possessing %s"), *(ControlledTank->GetName()));
    }
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
	AimTowardsCrosshair();
}

ATankRecreat* ATankPlayerController::GetTankController()const
{
    return Cast<ATankRecreat>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if(!GetTankController()){ return; }

    FVector HitLocation; //OUT parameter
    if(GetSightRayHitLocation(HitLocation))
    {
		UE_LOG(LogTemp, Warning, TEXT("LastHitLocation is: %s"),*LastHitLocation.ToString());

        GetTankController()->AimAt(HitLocation);
    }
}

//get world location of linetrace through crosshair 
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    //find the crosshair position in pixel coordinate
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);  
    
    //de-projevt the screen position to the world direction
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);  
    
    FVector LookDirection;
    if(GetLookDirection(ScreenLocation, LookDirection))
    {
        // linetrace along lookdirection and see what we hit
        GetLookVectorHitLocation(LookDirection, HitLocation); //TODO compare with course code
        return true;
    }

    return false;
}

// geting hit location by look direction 
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
    FHitResult HitResult;

    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (
        LookDirection * LineTraceRange);

    if(GetWorld()->LineTraceSingleByChannel( 
            HitResult, 
            StartLocation,
            EndLocation,  
            ECollisionChannel::ECC_Visibility))
        {
            UE_LOG(LogTemp, Warning, TEXT("Hit Actor Name is: %s"), *HitResult.Actor->GetName());

            HitLocation = HitResult.Location;

            return true;
        }

    return false;
    
}

// get look direction normalized ,converting pixel coordination to 3d direction
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation; //to be discarded
    return DeprojectScreenPositionToWorld(ScreenLocation.X,
    ScreenLocation.Y, 
    CameraWorldLocation, 
    LookDirection);
}
