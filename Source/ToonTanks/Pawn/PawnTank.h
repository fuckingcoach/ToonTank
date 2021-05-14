// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()
	

private:
	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Components", meta = (AllowPrivateAccess = "true"));
	USpringArmComponent* SpringArm ;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Components", meta = (AllowPrivateAccess = "true"));
	UCameraComponent* Camera ;
	//VARIABLES
	FVector MoveDirection;
	FQuat RotationDirection;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,category = "Movement",meta = (AllowPrivateAccess = "true"));
	float MoveSpeed = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Movement", meta = (AllowPrivateAccess = "true"));
	float RotateSpeed = 100.0f;

	APlayerController* PlayerControllerRef;
	bool bIsPlayerAlive = true;

	//FUNCTIONS
	void CalculateMove(float Value);
	void CalculateRotate(float Value);
	void Move();
	void Rotate();

public:
		APawnTank();

		virtual void HandleDestruction() override;
		
		// Called every frame
		virtual void Tick(float DeltaTime) override;

		//FUNCTIONS
		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

		bool GetIsPlayerAlive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
