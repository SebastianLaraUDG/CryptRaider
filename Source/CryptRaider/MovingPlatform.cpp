// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	startPos = GetActorLocation();

	FString myString;
	GetName(myString);


	UE_LOG(LogTemp, Warning, TEXT("Ejemplo de log temp WARNING: %s"), *myString);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(const float& DeltaTime) {

	if (ShouldPlatformReturn()) {
		FVector direccionMovimiento = platformVelocity.GetSafeNormal();
		startPos = startPos + direccionMovimiento * distanciaMaxima;
		SetActorLocation(startPos);
		platformVelocity = -platformVelocity;
	}
	else {
		FVector currentLocation = GetActorLocation();
		SetActorLocation(currentLocation + platformVelocity * DeltaTime);
	}
}

void AMovingPlatform::RotatePlatform(const float& DeltaTime) {
	AddActorLocalRotation(rotationVelocity * DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const {
	return GetDistanceMoved() > distanciaMaxima;
}

float AMovingPlatform::GetDistanceMoved() const {
	return FVector::Dist(startPos, GetActorLocation());
}
