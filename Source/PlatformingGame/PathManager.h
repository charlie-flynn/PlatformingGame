// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PathManager.generated.h"

class USplineComponent;

UCLASS()
class PLATFORMINGGAME_API APathManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APathManager();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USplineComponent* Path;

	TArray<AActor*> ActorsToBind;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void BindActor(AActor* ActorToBind);

	UFUNCTION(BlueprintCallable, 
		meta = (DisplayName = "Get Actor's Forward Rotation On Path", 
			ToolTip="Returns the forward rotation of the closest point to the given actor's position."))
	FVector GetForwardOnSpline(AActor* Actor);

	UFUNCTION(BlueprintCallable, 
		meta = (DisplayName = "Get Actor's Backward Rotation On Path", 
			ToolTip = "Returns the backward rotation of the closest point to the given actor's position."))
	FVector GetBackwardOnSpline(AActor* Actor);
};
