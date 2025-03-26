// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

/**
 * 
 */

class AEnemy;

UCLASS()
class EXOPHYSIQUE_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	


protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool hasWon;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float Score;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int currentBulletNumber;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int totalBulletNumber;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int controlledBulletNumber;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int basicBulletNumber;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int currentEnemyNumber;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class UMyUserWidget> WidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	class UMyUserWidget* MyWidgetInstance;

	bool OnCd;


	UFUNCTION()
	void OnEnemyDeath(float Value);

	UFUNCTION()
	void OnSlingShot();

	UFUNCTION()
	void AddEnemy();

	UFUNCTION()
	void OnBulletTypeChange(int type);

	UFUNCTION()
	void NoBulletAvailable();

	UFUNCTION()
	void LoseCooldown();


};
