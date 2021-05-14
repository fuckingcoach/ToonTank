// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawn/PawnTank.h"
#include "ToonTanks/Pawn/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"



void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}


void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	// Check type of Actor died, If is turret ,tally. If Player, set lose condition.
	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false);

		if (PlayerControllerref)
		{
			PlayerControllerref->SetPlayerEnabledState(false);
		}
	}
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();

		if (--TargetTurrets == 0)
		{
			HandleGameOver(true);
		}
	}
}

void ATankGameModeBase::HandleGameStart()
{
	// Initilaize start countdown, turret activation, pawn check etc.
	// Call BP version GameStart();

	TargetTurrets = GetTargetTurretCount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerref = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	GameStart();
	if (PlayerControllerref)
	{
		PlayerControllerref->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerref, &APlayerControllerBase::SetPlayerEnabledState, true);
		GetWorldTimerManager().SetTimer(PlayerEnableHandle,PlayerEnableDelegate,StartDealy,false);
	}

}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	// Chekc if Player destroy all Turrets , show win.
	// else if Turret destroy Player, show lose.
	// Call BP version GameOver(bool PlayerWon).
	GameOver(PlayerWon);
}


int32 ATankGameModeBase::GetTargetTurretCount()
{
	TArray<AActor*>  TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);

	return TurretActors.Num();
}