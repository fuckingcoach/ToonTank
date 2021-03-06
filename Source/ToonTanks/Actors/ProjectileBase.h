// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;

UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
private:
	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"));
	UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"));
	UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"));
	UParticleSystemComponent* ParticleTrail;
	//VARIABLES
	UPROPERTY(EditDefaultsOnly, category = "Damage");
	TSubclassOf<UDamageType> DamageType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Move", meta = (AllowPrivateAccess = "true"));
	float MovementSpeed = 1300.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Damage", meta = (AllowPrivateAccess = "true"));
	float Damage = 50.f;
	UPROPERTY(EditAnywhere, category = "Effects");
	UParticleSystem* HitParticle;
	UPROPERTY(EditAnywhere, category = "Effects");
	USoundBase* HitSound;
	UPROPERTY(EditAnywhere, category = "Effects");
	USoundBase* LaunchSound;
	UPROPERTY(EditAnywhere, category = "Effects");
	TSubclassOf<UCameraShake> HitShake;
	//FUNCTIONS
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,  UPrimitiveComponent* OtherComp,  FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
