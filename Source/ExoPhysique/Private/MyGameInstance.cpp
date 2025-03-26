// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameStateBase.h"

void UMyGameInstance::LoadNextGameLevel()
{
	CurrentLevel++;

	if (CurrentLevel >= Levels.Num())
		return;

	UGameplayStatics::OpenLevel(this, Levels[CurrentLevel]);

}

void UMyGameInstance::InitState()
{
	AMyGameStateBase* gameState = Cast<AMyGameStateBase>(GetWorld()->GetGameState());

	gameState->basicBulletNumber = LevelsBasicBulletCount[CurrentLevel];
	gameState->controlledBulletNumber = LevelsControlledBulletCount[CurrentLevel];

	gameState->currentBulletNumber = gameState->basicBulletNumber;
	gameState->totalBulletNumber = gameState->controlledBulletNumber + gameState->basicBulletNumber;

	gameState->OnBulletTypeChange(0);
}