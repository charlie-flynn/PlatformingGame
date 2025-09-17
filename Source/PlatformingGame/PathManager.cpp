// Fill out your copyright notice in the Description page of Project Settings.


#include "PathManager.h"
#include "Components/SplineComponent.h"

// Sets default values
APathManager::APathManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Path = CreateDefaultSubobject<USplineComponent>("Path");
}

// Called when the game starts or when spawned
void APathManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APathManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActorsToBind.IsEmpty()) return;

	for (AActor* actor : ActorsToBind)
	{
		FTransform actorTransform = actor->GetTransform();

		float inputKey = Path->FindInputKeyClosestToWorldLocation(actorTransform.GetLocation());

		FVector positionOnSpline = Path->GetLocationAtSplineInputKey(inputKey, ESplineCoordinateSpace::World);

		actorTransform.SetLocation(FVector(positionOnSpline.X, positionOnSpline.Y, actorTransform.GetLocation().Z));

		actor->SetActorTransform(actorTransform, false, NULL, ETeleportType::TeleportPhysics);
	}
}

void APathManager::BindActor(AActor* ActorToBind)
{
	ActorsToBind.Add(ActorToBind);
}

FVector APathManager::GetForwardOnSpline(AActor* Actor)
{
	float inputKey = Path->FindInputKeyClosestToWorldLocation(Actor->GetTransform().GetLocation());
	FVector direction = Path->GetRotationAtSplineInputKey(inputKey, ESplineCoordinateSpace::World).Euler();
	FVector::DegreesToRadians(direction);
	return direction;
}

FVector APathManager::GetBackwardOnSpline(AActor* Actor)
{
	return GetForwardOnSpline(Actor) * -1;
}

