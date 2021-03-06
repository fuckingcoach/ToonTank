// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.h"
#include "PawnTurret.generated.h"

class APawnTank;

UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()
	
private:

	//VARIABLES
	FTimerHandle FireRateTimerHandle;
	APawnTank* PlayerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"));
	float FireRate = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"));
	float FireRange = 500.0f;

	//FUNCTIONS
	void CheckFireCondition();
	float GetDistanceToPlayer();


public:
	APawnTurret();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//FUNCTIONS
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void HandleDestruction() override;
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
