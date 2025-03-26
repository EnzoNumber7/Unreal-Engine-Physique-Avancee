// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

class USphereComponent;
class UNiagaraSystem;
UCLASS()
class AEnemy : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void Init();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAcces = "true"))
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAcces = "true"))
	float WeightLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAcces = "true"))
	USphereComponent* SphereCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAcces = "true"))
	UNiagaraSystem* Explosion;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	void OnDeath();
};
