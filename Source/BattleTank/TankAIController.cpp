// Fill out your copyright notice in the Description page of Project Settings.


#include "TankRecreat.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

    auto ControlledAITank = GetAIControlledTank();
    if(!ControlledAITank)
    {
	    UE_LOG(LogTemp, Warning,TEXT("AIcontroller not possessing a tank"));
    }
    else
    {
	    UE_LOG(LogTemp, Warning,TEXT("AIcontroller possessing %s"), *(ControlledAITank->GetName()));
    }

    auto TankPlayer = GetPlayerTank();
    if(!TankPlayer)
    {
	    UE_LOG(LogTemp, Warning,TEXT("TankPlayer is not found by AIcontroller"));
    }
    else
    {
	    UE_LOG(LogTemp, Warning,TEXT("TankPlayer %s is found by AIController"), *(TankPlayer->GetName()));
    }
}

ATankRecreat* ATankAIController::GetPlayerTank() const 
{
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    
    if(!PlayerPawn){ return nullptr; }

    return Cast<ATankRecreat>(PlayerPawn);
}

void ATankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
    
    GetAIControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}

ATankRecreat* ATankAIController::GetAIControlledTank()const
{
    return Cast<ATankRecreat>(GetPawn());
}