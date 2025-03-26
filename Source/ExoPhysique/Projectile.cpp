
#include "Projectile.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "Field/FieldSystemActor.h"
#include "ExoPhysique/ExoPhysiqueCharacter.h"
#include "Camera/CameraComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	_meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = _meshComp;
	_meshComp->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	_meshComp->OnComponentHit.AddDynamic(this, &AProjectile::OnBeginCollision);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	if (_projectileMesh)
	{
		_meshComp->SetStaticMesh(_projectileMesh);
		_meshComp->SetSimulatePhysics(true);
		_meshComp->SetNotifyRigidBodyCollision(true);

		_meshComp->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
		_meshComp->SetMaterial(0,_material);
		_meshComp->BodyInstance.bLockZRotation = true;

	}

	FTimerHandle TimerHandle_LifeTime;
	FTimerDelegate Delegate; // Delegate to bind function with parameters
	Delegate.BindUFunction(this, "DestroyProjectile");

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_LifeTime, Delegate, _lifeTime, false);

	_onCd = false;
	_fieldHasSpawned = false;

}

void AProjectile::OnBeginCollision(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (_projectileField && !_fieldHasSpawned)
	{
		UWorld* const World = GetWorld();
		FVector SpawnPos = GetActorLocation();
		AFieldSystemActor* field = World->SpawnActor<AFieldSystemActor>(_projectileField, SpawnPos,GetActorRotation());
		field->SetActorScale3D(FVector(2, 2, 2));
		_fieldHasSpawned = true;

		APlayerController* controller = Cast<APlayerController>(GetController());
		if (controller && !_onCd)
		{
			_onCd = true;
			FTimerHandle TimerHandle_UnpossessCd;
			FTimerDelegate Delegate; // Delegate to bind function with parameters
			Delegate.BindUFunction(this, "PossessCharacter");

			GetWorld()->GetTimerManager().SetTimer(TimerHandle_UnpossessCd, Delegate, _unpossessCd, false);

			UCameraComponent* camera = Cast< UCameraComponent>(_meshComp->GetChildComponent(0));
			
			camera->DetachFromParent(true);
		}
		
	}

}

void AProjectile::PossessCharacter()
{
	APlayerController* controller = Cast<APlayerController>(GetController());
	controller->UnPossess();
	controller->Possess(_shooterPawn);
}

void AProjectile::LaunchProjectile(APawn* shooterPawn, FVector direction,float baseImpulse)
{

	_shooterPawn = shooterPawn;

	if (baseImpulse != -1)
		_baseImpulse = baseImpulse;

	UPrimitiveComponent* projectileComp = Cast<UPrimitiveComponent>(GetRootComponent());

	if (projectileComp)
	{
		direction.Normalize();
		projectileComp->AddImpulse(_baseImpulse * direction,NAME_None,true);
		
	}
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AProjectile::DestroyProjectile()
{
	APlayerController* controller = Cast<APlayerController>(GetController());
	if (controller)
	{
		controller->UnPossess();
		controller->Possess(_shooterPawn);
	}

	Destroy();
}


