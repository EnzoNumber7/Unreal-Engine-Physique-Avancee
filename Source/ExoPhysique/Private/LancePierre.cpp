#include "LancePierre.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "../Projectile.h"
#include "MyGameStateBase.h"

// Sets default values
ALancePierre::ALancePierre()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALancePierre::BeginPlay()
{
	Super::BeginPlay();
	isAiming = false;
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController) {
		PlayerController->bShowMouseCursor = true;
	}
	Direction = SpawnPosition - sphereMesh->GetComponentLocation();

	CurrentProjectile = Projectile;


}

// Called every frame
void ALancePierre::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isAiming) {
		Look();
	}

}

void ALancePierre::StartAim()
{
	isAiming = true;
}

void ALancePierre::StopAim()
{
	isAiming = false;
}

void ALancePierre::AdjustPower(const FInputActionValue& Value)
{
	float ScrollValue = Value.Get<float>();


	force += ScrollValue * 200;


	force = FMath::Clamp(force, 1000, 5000);

	UE_LOG(LogTemp, Warning, TEXT("PowerFactor: %f"), force);
}

void ALancePierre::Look_Implementation()
{

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	float X, Y;
	if (!PlayerController->GetMousePosition(X, Y))
	{
		return;
	}
	FVector WorldLocation, WorldDirection;
	if (PlayerController->DeprojectScreenPositionToWorld(X, Y, WorldLocation, WorldDirection))
	{
		FVector TargetPosition = WorldLocation + (WorldDirection * 100.f);

		FVector NewPosition = sphereMesh->GetComponentLocation();
		NewPosition.X = TargetPosition.X;
		NewPosition.Z = TargetPosition.Z;


		sphereMesh->SetWorldLocation(NewPosition);
		Direction = SpawnPosition - sphereMesh->GetComponentLocation();


		UObject* world = GetWorld();
		APlayerCameraManager* cameraManager = UGameplayStatics::GetPlayerCameraManager(world, 0);

		Direction.Normalize();

		if (Direction * force == FVector::ZeroVector)
			return;

		FPredictProjectilePathParams param;
		param.MaxSimTime = 2.f;
		param.StartLocation = SpawnPosition;
		param.LaunchVelocity = Direction * force;
		param.bTraceWithCollision = false;
		param.TraceChannel = ECC_Visibility;
		param.ProjectileRadius = 10;
		param.SimFrequency = 10;
		FPredictProjectilePathResult result;


		UGameplayStatics::PredictProjectilePath(this, param, result);


		TrajectoryPosition.Empty();
		for (int i = 0; i < result.PathData.Num(); i++)
		{
			TrajectoryPosition.Add(result.PathData[i].Location);
		}
	}
}

void ALancePierre::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInput = Cast< UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(ShootAction, ETriggerEvent::Started, this, &ALancePierre::Shoot);
		EnhancedInput->BindAction(AimAction, ETriggerEvent::Started, this, &ALancePierre::StartAim);
		EnhancedInput->BindAction(AimAction, ETriggerEvent::Completed, this, &ALancePierre::StopAim);
		EnhancedInput->BindAction(ScrollAction, ETriggerEvent::Triggered, this, &ALancePierre::AdjustPower);
		EnhancedInput->BindAction(SwitchBulletAction, ETriggerEvent::Started, this, &ALancePierre::ChangeBullet);

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed Input Coponent"));
	}

}

void ALancePierre::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
			UE_LOG(LogTemp, Warning, TEXT("Link MappingContext"));
		}
	}
}

void ALancePierre::Shoot()
{

	if (CurrentProjectile != nullptr)
	{
		AMyGameStateBase* gameState = Cast<AMyGameStateBase>(GetWorld()->GetGameState());

		if (gameState->currentBulletNumber <= 0)
			return;

		gameState->OnSlingShot();

		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			APlayerController* PlayerController = Cast<APlayerController>(GetController());


			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			FVector rotationVector = FVector(Direction.X, Direction.Y, 0);
			FRotator SpawnRotation = rotationVector.Rotation();

			// Spawn the projectile at the muzzle
			AProjectile* proj = World->SpawnActor<AProjectile>(CurrentProjectile, SpawnPosition, SpawnRotation, ActorSpawnParams);
			proj->LaunchProjectile(this, Direction, force);

			PlayerController->UnPossess();
			PlayerController->Possess(proj);
			isAiming = false;

			Direction.Normalize();


		}
	}
}

void ALancePierre::ChangeBullet()
{
	AMyGameStateBase* gameState = Cast<AMyGameStateBase>(GetWorld()->GetGameState());

	if (CurrentProjectile == Projectile)
	{
		CurrentProjectile = ControlledProjectile;
		gameState->OnBulletTypeChange(1);
	}
	else
	{
		CurrentProjectile = Projectile;
		gameState->OnBulletTypeChange(0);
	}
}