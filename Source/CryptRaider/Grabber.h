// Sebas INC. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Grabber.generated.h"

class UPhysicsHandleComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Release() const;

	UFUNCTION(BlueprintCallable)
	void Grab() const;

private:

	// En centimetros
	UPROPERTY(EditAnywhere)
	float maxGrabDistance = 400.0f;


	UPROPERTY(EditAnywhere)
	float holdDistance = 200.0f;

	
	UPROPERTY(EditAnywhere)
	float grabRadius = 100.0f;

	UPhysicsHandleComponent* GetPhysicsHandle() const;
	bool GetGrabbableInReach(FHitResult& OutHitResult) const;
};
