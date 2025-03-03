// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class CRYPTRAIDER_API AMovingPlatform : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Moving")
	FVector platformVelocity;

	FVector startPos;

	UPROPERTY(EditAnywhere, Category = "Moving")
	float distanciaMaxima;

	UPROPERTY(EditAnywhere, Category = "Rotation")
	FRotator rotationVelocity;

	void MovePlatform(const float&);

	void RotatePlatform(const float&);

	bool ShouldPlatformReturn() const;

	float GetDistanceMoved() const;
};
