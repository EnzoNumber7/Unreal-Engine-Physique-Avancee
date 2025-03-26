// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Projectile.h"
#include "ControlledProjectile.generated.h"

/**
 * 
 */

UCLASS()
class EXOPHYSIQUE_API AControlledProjectile : public AProjectile
{
	GENERATED_BODY()

public:

	AControlledProjectile();


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NotifyControllerChanged() override;

protected:
	virtual void BeginPlay() override;

	void Move(const struct FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float DirectionnalForce;
	
};
