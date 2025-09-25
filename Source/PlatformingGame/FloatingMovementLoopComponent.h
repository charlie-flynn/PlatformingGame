// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FloatingMovementLoopComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATFORMINGGAME_API UFloatingMovementLoopComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPROPERTY(EditAnywhere)
	float FloatRange;

	UPROPERTY(EditAnywhere)
	float FloatSpeed;

	// Sets default values for this component's properties
	UFloatingMovementLoopComponent();

private:
	AActor* owner;

	float floatingTimer;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
