// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"


void UTankBarrel::ElevateBarrel(float RelativeSpeed)
{
    float ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

    float ElevateChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

    float RawNewElevation = GetRelativeRotation().Pitch + ElevateChange;

    float ClampedElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

    SetRelativeRotation(FRotator(ClampedElevation, 0.0, 0.0));
}