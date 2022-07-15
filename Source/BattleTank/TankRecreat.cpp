// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankRecreat.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATankRecreat::ATankRecreat()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATankRecreat::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATankRecreat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATankRecreat::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATankRecreat::SetBarrelRefrence(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelRefrence(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATankRecreat::SetTurretRefrence(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretRefrence(TurretToSet);
}

void ATankRecreat::Fire()
{
	if(!Barrel){ return; }
	FVector ProjectileSocketLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FRotator ProjectileSocketRotation = Barrel->GetSocketRotation(FName("Projectile"));
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, ProjectileSocketLocation, ProjectileSocketRotation);

	Projectile->LaunchProjecctile(LaunchSpeed);
}


