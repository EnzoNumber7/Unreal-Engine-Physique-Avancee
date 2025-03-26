// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Projectile.generated.h"

UCLASS()
class EXOPHYSIQUE_API AProjectile : public APawn
{
	GENERATED_BODY()

public:

	AProjectile();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void LaunchProjectile(APawn* character,FVector direction, float baseImpulse = -1);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginCollision(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void DestroyProjectile();

	class APawn* _shooterPawn;

	UStaticMeshComponent* _meshComp;
private:

	UFUNCTION()
	void PossessCharacter();

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	float _baseImpulse;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	UStaticMesh* _projectileMesh;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	float _lifeTime;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float _unpossessCd;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	TSubclassOf<class AFieldSystemActor> _projectileField;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	UMaterialInterface* _material;


	bool _onCd;

	bool _fieldHasSpawned;




};
