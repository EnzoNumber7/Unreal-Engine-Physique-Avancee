// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class EXOPHYSIQUE_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void Win();

	UFUNCTION(BlueprintImplementableEvent)
	void Lose();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateScore();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateBullet();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateBulletType(int type);
};
