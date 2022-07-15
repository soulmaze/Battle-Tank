// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation,float LaunchSpeed) 
{
	if(!Barrel){ return; }
	FVector LaunchVelocity = FVector(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this, 
		LaunchVelocity, 
		StartLocation, 
		HitLocation, 
		LaunchSpeed, 
		false, 
		0, 
		0, 
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if(this->GetOwner()->GetName() == FString("BP_Tank_C_0"))
	{
		UE_LOG(LogTemp, Warning, TEXT("hitlocation is: %s"),*HitLocation.ToString());
	}

	if(bHaveAimSolution)
	{
		// UE_LOG(LogTemp, Warning, TEXT("bhaveaimsolution is true"));
		FVector AimDirection = LaunchVelocity.GetSafeNormal(); 
		// UE_LOG(LogTemp, Warning, TEXT("aimdirection is at %s"),*AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
		
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f :aimsolution found"), Time);
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f :no aim solution found"), Time);
	}
}

void UTankAimingComponent::SetBarrelRefrence(UTankBarrel* BarrelToSet) 
{
	if(!BarrelToSet){ return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretRefrence(UTankTurret* TurretToSet) 
{
	if(!TurretToSet){ return; }
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimDirectionRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimDirectionRotator - BarrelRotator;
	Barrel->ElevateBarrel(DeltaRotator.Pitch);
	Turret->RotateTurret(DeltaRotator.Yaw);
}

