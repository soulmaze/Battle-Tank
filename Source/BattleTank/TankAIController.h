// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATankRecreat;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	ATankRecreat* GetAIControlledTank()const;
	
	virtual void BeginPlay() override;

	ATankRecreat* GetPlayerTank() const;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
