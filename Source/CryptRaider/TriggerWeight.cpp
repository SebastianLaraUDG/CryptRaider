// Sebas INC. All rights reserved


#include "TriggerWeight.h"
#include "Mover.h"

UTriggerWeight::UTriggerWeight()
{
	PrimaryComponentTick.bCanEverTick = true;
	Mover = nullptr;
}

void UTriggerWeight::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerWeight::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
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

AActor* UTriggerWeight::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	float pesoCargado = 0.0f;

	for (AActor* Actor : Actors) {
		bool IsGrabbed = Actor->ActorHasTag("Grabbed");
		
		UPrimitiveComponent* component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if (component)
			pesoCargado += component->GetMass();

		UE_LOG(LogTemp, Display, TEXT("Peso acumulado: %f"), pesoCargado);
		if (Actor->ActorHasTag(UnlockTag) && !IsGrabbed && pesoCargado >= WeightToActivate)
			return Actor;
	}
	return nullptr;
}
