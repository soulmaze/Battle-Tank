// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankRecreat.generated.h"

// Forward declarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATankRecreat : public APawn
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, category = Setup)
	void SetBarrelRefrence(UTankBarrel* BarrelToSet);
	
	UFUNCTION(BlueprintCallable, category = Setup)
	void SetTurretRefrence(UTankTurret* TurretToSet);
	
	UFUNCTION(BlueprintCallable, category = Firing)
	void Fire();

	void AimAt(FVector HitLocation);

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATankRecreat();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, category = Firing)
	float LaunchSpeed = 4000; //sensible starting value of 100 m/s

	UPROPERTY(EditAnywhere, category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// local reference for barrel
	UTankBarrel* Barrel = nullptr;
};
