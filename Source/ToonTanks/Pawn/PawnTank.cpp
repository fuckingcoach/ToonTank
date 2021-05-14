// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


APawnTank::APawnTank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set Components.
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
}

// If player has been destroyed,hide it.
void APawnTank::HandleDestruction()
{
	Super::HandleDestruction();

	bIsPlayerAlive = false;
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move();
	Rotate();

	// Let turret rotate toward mouse cursor.
	if (PlayerControllerRef)
	{
		FHitResult TraceHitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
		FVector HitLocation = TraceHitResult.ImpactPoint;

		RotateTurret(HitLocation);
	}
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMove);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotate);
	PlayerInputComponent->BindAction("Fire",IE_Pressed,this,&APawnTank::Fire);

}

bool APawnTank::GetIsPlayerAlive()
{
	return bIsPlayerAlive;
}

void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection,true);
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(RotationDirection,true);
}

void APawnTank::CalculateMove(float Value)
{
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds,0,0);

}

void APawnTank::CalculateRotate(float Value)
{
	float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotateAmount, 0);
	RotationDirection = FQuat(Rotation);
}
