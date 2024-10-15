// Sebas INC. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "TriggerComponent.h"
#include "TriggerWeight.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UTriggerWeight : public UTriggerComponent
{
	GENERATED_BODY()

public:
	UTriggerWeight();
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY(EditAnywhere)
	float WeightToActivate;
protected:
	AActor* GetAcceptableActor() const override;
};
