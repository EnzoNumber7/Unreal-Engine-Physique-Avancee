// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class EXOPHYSIQUE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	int CurrentLevel;

	UFUNCTION(BlueprintCallable)
	void LoadNextGameLevel();

	void InitState();

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	TArray<FName> Levels;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<int> LevelsBasicBulletCount;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<int> LevelsControlledBulletCount;
	
};
