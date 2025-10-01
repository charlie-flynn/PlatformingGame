// Fill out your copyright notice in the Description page of Project Settings.


#include "PathBindComponent.h"
#include "PathManager.h"

// Sets default values for this component's properties
UPathBindComponent::UPathBindComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

	PathManager = CreateDefaultSubobject<APathManager>("PathManager");
}


// Called when the game starts
void UPathBindComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPathBindComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

