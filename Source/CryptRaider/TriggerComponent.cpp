// Sebas INC. All rights reserved


#include "TriggerComponent.h"
#include "Mover.h"
#include "Components/CapsuleComponent.h"


UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	UnlockTag = FName(TEXT("Gargoyle"));
	Mover = nullptr;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	UMover* mover = GetOwner()->GetComponentByClass<UMover>();
	if (mover)
		SetMover(mover);
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Mover)
		return;

	AActor* Actor = GetAcceptableActor();

	if (Actor) {
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if (Component) {
			UE_LOG(LogTemp, Display, TEXT("Unlocking"));
			Component->SetSimulatePhysics(false);
			Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
			Mover->SetShouldMove(true);
		}
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("Relocking"));
		Mover->SetShouldMove(false);
	}
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors) {
		bool IsGrabbed = Actor->ActorHasTag("Grabbed");
		if (Actor->ActorHasTag(UnlockTag) && !IsGrabbed)
			return Actor;
	}
	return nullptr;
}

void UTriggerComponent::SetMover(UMover* newMover) {
	Mover = newMover;
}