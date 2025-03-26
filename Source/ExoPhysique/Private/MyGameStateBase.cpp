
#include "MyGameStateBase.h"
#include "MyUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "MyGameInstance.h"

void AMyGameStateBase::BeginPlay()
{
	Score = 0;
	currentEnemyNumber = 0;
	hasWon = false;
	if (WidgetClass) {
		MyWidgetInstance = CreateWidget<UMyUserWidget>(GetWorld(), WidgetClass);
		if (MyWidgetInstance) {
			MyWidgetInstance->AddToViewport();
		}
	}
	
	Cast<UMyGameInstance>(GetGameInstance())->InitState();

	MyWidgetInstance->UpdateBullet();
	OnCd = false;

}

void AMyGameStateBase::OnEnemyDeath(float Value)
{
	currentEnemyNumber--;
	Score += Value;
	MyWidgetInstance->UpdateScore();
	if (currentEnemyNumber <= 0) {
		hasWon = true;
		MyWidgetInstance->Win();
	}
}

void AMyGameStateBase::OnSlingShot()
{
	if (currentBulletNumber <= 0)
	{
		return;
	}

	currentBulletNumber--;
	totalBulletNumber--;
	MyWidgetInstance->UpdateBullet();
	
	if (totalBulletNumber == 0)
		NoBulletAvailable();
}

void AMyGameStateBase::AddEnemy()
{
	currentEnemyNumber++;
}

void AMyGameStateBase::OnBulletTypeChange(int type)
{
	if (type == 0)
	{
		currentBulletNumber = basicBulletNumber;
	}

	else
	{
		currentBulletNumber = controlledBulletNumber;
	}
	MyWidgetInstance->UpdateBulletType(type);
	MyWidgetInstance->UpdateBullet();

}

void AMyGameStateBase::NoBulletAvailable()
{
	if (OnCd)
		return;

	FTimerHandle TimerHandle_Lose;
	FTimerDelegate Delegate; // Delegate to bind function with parameters
	Delegate.BindUFunction(this, "LoseCooldown");

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Lose, Delegate, 5.0f, false);
}

void AMyGameStateBase::LoseCooldown()
{
	OnCd = false;
	MyWidgetInstance->Lose();
}


