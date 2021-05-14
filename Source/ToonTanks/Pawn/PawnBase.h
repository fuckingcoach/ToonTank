// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "Particles/ParticleSystem.h"
#include "PawnBase.generated.h"

class UCapsuleComponent;
class AProjectileBase;
class UHealthComponent;

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

private:
	//Components
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,category = "Components", meta = (AllowPrivateAccess = "true"));
	UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"));
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"));
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"));
	USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"));
	UHealthComponent* HealthComponent;

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Projectile Type", meta = (AllowPrivateAccess = "true"));
	TSubclassOf<AProjectileBase> ProjectileClass;
	UPROPERTY(EditAnywhere, category = "Effects");
	UParticleSystem* DeathParticle;
	UPROPERTY(EditAnywhere, category = "Effects");
	USoundBase* DeathSound;
	UPROPERTY(EditAnywhere, category = "Effects");
	TSubclassOf<UCameraShake> DeathShake;

public:


	// Sets default values for this pawn's properties
	APawnBase();

	//FUNCTIONS
	virtual void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//FUNCTIONS
	void RotateTurret(FVector LookAtTarget);

	void Fire();

	

};
