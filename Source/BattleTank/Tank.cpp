// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATank::SetTurretChildActor(UChildActorComponent* TurretFromBP) 
{
	UE_LOG(LogTemp, Warning,TEXT("SetTurretChildActor called"));

	if(!TurretFromBP){ return;}

	Turret = TurretFromBP;
}

void ATank::SetBarrelChildActor(UChildActorComponent* BarrelFromBP) 
{
	UE_LOG(LogTemp, Warning,TEXT("SetBarrelChildActor called"));

	if(!BarrelFromBP){ return;}

	Barrel = BarrelFromBP;
}

void ATank::SetTankBodyChildActor(UChildActorComponent* TankFromBP) 
{
	UE_LOG(LogTemp, Warning,TEXT("SetTankChildActor called"));

	if(!TankFromBP){ return;}

	Tank = TankFromBP;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("Turret_Rotation", this, &ATank::RotateTurret);

	PlayerInputComponent->BindAxis("Barrel_Elevation", this, &ATank::ElevateBarrel);
	
	PlayerInputComponent->BindAxis("Tank_Move", this, &ATank::MoveTank);
	
	PlayerInputComponent->BindAxis("Tank_Rotation", this, &ATank::RotateTank);
}

void ATank::RotateTurret(float Speed) 
{
	if(!Turret){ return; }
	
	float Rotation = GetWorld()->DeltaTimeSeconds * Speed * RotationSpeed;
	Turret->AddRelativeRotation(FRotator(0.f, Rotation, 0.f));
}

void ATank::ElevateBarrel(float Speed) 
{
	if(!Barrel){ return; }

	float Rotation = GetWorld()->DeltaTimeSeconds * Speed * RotationSpeed;
	Barrel->AddRelativeRotation(FRotator(Rotation, 0.f, 0.f));
}

void ATank::MoveTank(float Speed) 
{
	if(!Tank){ return; }
	
	float Distance = GetWorld()->DeltaTimeSeconds * Speed * MovementSpeed;
	Tank->AddRelativeLocation(Tank->GetForwardVector() * Distance);
}

void ATank::RotateTank(float Speed) 
{
	if(!Tank){ return; }

	float Rotation = GetWorld()->DeltaTimeSeconds * Speed * RotationSpeed;
	Tank->AddRelativeRotation(FRotator(0.f, Rotation, 0.f));
}





