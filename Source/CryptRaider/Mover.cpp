// Sebas INC. All rights reserved


#include "Mover.h"

#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	ShouldMove = false;
	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();
	// ...
	OriginalLocation = GetOwner()->GetActorLocation();
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector TargetLocation = OriginalLocation;
	if (ShouldMove) {
		TargetLocation = OriginalLocation + MoveOffset;
	}
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	float speed = MoveOffset.Length() / MoveTime;
	FVector newLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, speed);
	GetOwner()->SetActorLocation(newLocation);
	
}

void UMover::SetShouldMove(const uint8& bShouldMove)
{
	ShouldMove = bShouldMove;
}

