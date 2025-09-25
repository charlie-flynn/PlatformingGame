// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingMovementLoopComponent.h"

// Sets default values for this component's properties
UFloatingMovementLoopComponent::UFloatingMovementLoopComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	FloatRange = 1.0f;
	FloatSpeed = 1.0f;

	// ...
}


// Called when the game starts
void UFloatingMovementLoopComponent::BeginPlay()
{
	Super::BeginPlay();

	owner = GetOwner();

	// ...
	
}


// Called every frame
void UFloatingMovementLoopComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// timer moves faster the faster the floating is
	floatingTimer += DeltaTime * FloatSpeed;

	FTransform newTransform = owner->GetTransform();
	FVector currentPosition = newTransform.GetTranslation();

	newTransform.SetTranslation(
		FVector(currentPosition.X, 
			currentPosition.Y, 
			currentPosition.Z + (sin(floatingTimer) * FloatRange * FloatSpeed)));
	// reason why we multiply it by range *and* speed is to make it so the range of movement is unaffected by the speed

	owner->SetActorTransform(newTransform);
}

