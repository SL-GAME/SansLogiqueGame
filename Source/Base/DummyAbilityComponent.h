// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerAbilityComponent.h"
#include "DummyAbilityComponent.generated.h"

class ADummyPawnProjectionClass;
class ADummyPawn;
/**
 * 
 */
UCLASS()
class BASE_API UDummyAbilityComponent : public UPlayerAbilityComponent
{
	GENERATED_BODY()
	
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ADummyPawnProjectionClass* dummyProjection;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float distanceDropDummy;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool isDummyCooldown;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float cooldownDummyMax;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool dummyUsable;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool leftActionUsed;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float maxAngleValue;

public:
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ADummyPawnProjectionClass>	projectionToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ADummyPawn>	dummyToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when component is activate
	virtual void OnActivated(UActorComponent* Component, bool Reset) override;

	// Called when component is desactivate
	virtual void OnDeactivated(UActorComponent* Component) override;

	// Shoot a ray and return target object, hit point and normal
	void shootRay(AActor*& hitTarget, FVector& hitPoint, FVector& impactNormal);

	// Return the distance of the player with the projection
	float getDistanceWithProjection();

	// Give the angle between a vector and the player vector up
	float getAngleWithPlayer(FVector normalOfObject);

	// Perform an ensemble of test to place the projection and tell to the player if he can spawn the dummy
	void placeProjection(AActor*& hitTarget, FVector& hitPoint, FVector& impactNormal);

	// Destroy the projection if it exist but new ray doesnt hit actor or with bad angle
	void destroyProjectionNewRay();

	// Spawn the dummy and return true if it's worked
	bool spawnDummy();

public:
	// Sets default values for this component's properties
	UDummyAbilityComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called when leftAction is pressed
	virtual void LeftActionPressed() override;

	// Called when leftAction is released
	virtual void LeftActionReleased() override;

	// Called when rightAction is pressed
	virtual void RightActionPressed() override;

	// Called after a few delay after rightAction pressed
	void RightActionPressedDelayed();

	// Called when rightAction is released
	virtual void RightActionReleased() override;

};
