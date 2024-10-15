// Sebas INC. All rights reserved


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"



// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();

	if (physicsHandle && physicsHandle->GetGrabbedComponent() != nullptr) {
		FVector targetLocation = GetComponentLocation() + GetForwardVector() * holdDistance;
		physicsHandle->SetTargetLocationAndRotation(targetLocation, GetComponentRotation());
	}
}

void UGrabber::Release() const{
	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();
	
	if (physicsHandle && physicsHandle->GetGrabbedComponent()) {
		physicsHandle->GetGrabbedComponent()->GetOwner()->Tags.Remove(TEXT("Grabbed"));
		physicsHandle->ReleaseComponent();
	}

	UE_LOG(LogTemp, Display, TEXT("Grabber released"));
}

void UGrabber::Grab() const
{
	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();
	if (!physicsHandle)
		return;

	FHitResult hitResult;
	bool hasHit = GetGrabbableInReach(hitResult);

	if (hasHit) {
		UPrimitiveComponent* hitComponent = hitResult.GetComponent();
		hitComponent->SetSimulatePhysics(true);
		hitComponent->WakeAllRigidBodies();
		hitResult.GetActor()->Tags.Add(TEXT("Grabbed"));
		hitComponent->GetOwner()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		physicsHandle->GrabComponentAtLocationWithRotation(
			hitComponent,
			NAME_None,
			hitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
	//DrawDebugLine(GetWorld(), start, end, FColor::Emerald);

	//UE_LOG(LogTemp, Display, TEXT("Grabber grabbed"));
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* physicsHandle = GetOwner()->GetComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandle)
		return physicsHandle;
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Physics Handle found"));
		return nullptr;
	}
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * maxGrabDistance;

	FCollisionShape sphere = FCollisionShape::MakeSphere(grabRadius);
	return GetWorld()->SweepSingleByChannel(
		OutHitResult, start, end,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2 // C:\Users\Public\Documents\CryptRaider\Config\DefaultEngine.ini
		, sphere);
}