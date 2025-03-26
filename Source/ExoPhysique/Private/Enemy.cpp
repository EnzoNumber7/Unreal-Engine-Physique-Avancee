
#include "Enemy.h"
#include "../Projectile.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "../Public/MyGameStateBase.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (SphereCollider) {
		SphereCollider->OnComponentHit.AddDynamic(this, &AEnemy::OnHit);
	}

	FTimerHandle TimerHandle_Init;
	FTimerDelegate Delegate; // Delegate to bind function with parameters
	Delegate.BindUFunction(this, "Init");
	 
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Init, Delegate, 0.2f, false);

}

void AEnemy::Init()
{
	AMyGameStateBase* myGameState = GetWorld()->GetGameState<AMyGameStateBase>();
	myGameState->AddEnemy();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	float ImpactForce = NormalImpulse.Size();
	if (AProjectile* proj = Cast<AProjectile>(OtherActor)) {
		OnDeath();
	}
	else if(!OtherActor->ActorHasTag("Ground")) {
		if (ImpactForce > WeightLimit) {
			OnDeath();
		}
	}
	else {
		if (ImpactForce > 200000) {
			OnDeath();
		}
	}
}

void AEnemy::OnDeath()
{
	AMyGameStateBase* myGameState = GetWorld()->GetGameState<AMyGameStateBase>();
	myGameState->OnEnemyDeath(Value);
	if (Explosion)
	{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),  // Récupère le monde en cours
			Explosion,   // Le Niagara System à spawner
			SphereCollider->GetComponentLocation(), // Position de l'ennemi
			GetActorRotation()  // Rotation de l'ennemi
		);
	}
	this->Destroy();
}

