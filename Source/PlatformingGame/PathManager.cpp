// Fill out your copyright notice in the Description page of Project Settings.


#include "PathManager.h"
#include "Components/SplineComponent.h"
#include "PathBindComponent.h"

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

	if (BoundActors.IsEmpty()) return;

	

	for (int i = 0; i < BoundActors.Num(); i++)
	{
		if (!IsValid(BoundActors[i]))
		{
			BoundActors.RemoveAt(i);
			break;
		}

		// get the input key closest to the actor's world position, then set the actor's x & y coordinates to the position on the spline at the given input key
		FVector actorPosition = BoundActors[i]->GetActorLocation();
		float inputKey = Path->FindInputKeyClosestToWorldLocation(actorPosition);

		FVector positionOnSpline = Path->GetLocationAtSplineInputKey(inputKey, ESplineCoordinateSpace::World);
		actorPosition = FVector(positionOnSpline.X, positionOnSpline.Y, actorPosition.Z);
		BoundActors[i]->SetActorLocation(actorPosition, false, nullptr, ETeleportType::TeleportPhysics);
	}
}

void APathManager::BindActor(AActor* ActorToBind)
{
	// if the actor has a pathbind component, set its PathManager to this instance
	UPathBindComponent* pathBind = ActorToBind->GetComponentByClass<UPathBindComponent>();
	if (pathBind)
		pathBind->PathManager = this;
		
	BoundActors.Add(ActorToBind);
}

FRotator APathManager::GetForwardOnSpline(AActor* Actor)
{
	float inputKey = Path->FindInputKeyClosestToWorldLocation(Actor->GetTransform().GetLocation());
	FRotator direction = Path->GetRotationAtSplineInputKey(inputKey, ESplineCoordinateSpace::World);
	return direction;
}

FRotator APathManager::GetBackwardOnSpline(AActor* Actor)
{
	return GetForwardOnSpline(Actor) * -1;
}

