// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	//-1 in min downward movement and +1 is max up movement 
	void ElevateBarrel(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, category = Setup)
	float MaxDegreesPerSecond = 10;
	
	UPROPERTY(EditAnywhere, category = Setup)
	float MinElevationDegrees = 0;
	
	UPROPERTY(EditAnywhere, category = Setup)
	float MaxElevationDegrees = 40;
};
