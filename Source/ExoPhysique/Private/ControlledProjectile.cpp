// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlledProjectile.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

AControlledProjectile::AControlledProjectile()
{
}

void AControlledProjectile::BeginPlay()
{
	Super::BeginPlay();
	_meshComp->SetEnableGravity(false);
}

void AControlledProjectile::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	UE_LOG(LogTemp, Warning, TEXT("X : %f"), MovementVector.X);

	if (Controller != nullptr)
	{
		_meshComp->AddImpulse(MovementVector.Y * _meshComp->GetUpVector() * DirectionnalForce);
		_meshComp->AddImpulse(MovementVector.X * _meshComp->GetRightVector() * DirectionnalForce);
	}
}

void AControlledProjectile::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AControlledProjectile::Move);

	}
}

void AControlledProjectile::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
			UE_LOG(LogTemp, Warning, TEXT("Link MappingContext"));
		}
	}
}