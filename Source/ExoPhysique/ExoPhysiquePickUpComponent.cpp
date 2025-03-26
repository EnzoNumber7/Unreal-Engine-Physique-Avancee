// Copyright Epic Games, Inc. All Rights Reserved.

#include "ExoPhysiquePickUpComponent.h"

UExoPhysiquePickUpComponent::UExoPhysiquePickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UExoPhysiquePickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UExoPhysiquePickUpComponent::OnSphereBeginOverlap);
}

void UExoPhysiquePickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AExoPhysiqueCharacter* Character = Cast<AExoPhysiqueCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
