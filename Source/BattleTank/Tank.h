// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Tank)
	void SetTurretChildActor(UChildActorComponent* TurretFromBP);

	UFUNCTION(BlueprintCallable, Category = Tank)
	void SetBarrelChildActor(UChildActorComponent* BarrelFromBP);
	
	UFUNCTION(BlueprintCallable, Category = Tank)
	void SetTankBodyChildActor(UChildActorComponent* TankFromBP);

private:
	// a refrence from blueprint
	void RotateTurret(float Speed);

	UChildActorComponent* Turret = nullptr;

	// a refrence from blueprint
	UChildActorComponent* Barrel = nullptr;

	void ElevateBarrel(float Speed);
	
	void RotateTank(float Speed);
	void MoveTank(float Speed);

	// a refrence from blueprint
	UChildActorComponent* Tank = nullptr;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 120.f;
	
	UPROPERTY(EditAnywhere)
	float MovementSpeed = 100.f;

};
