// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NinjaCharacterMovementComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CustomCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class BASE_API UCustomCharacterMovementComponent : public UNinjaCharacterMovementComponent
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool UseSmoothRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SmoothRate;

protected:
	/**
	 * Sets a new value for ThresholdParallelAngle.
	 * @note The new value is clamped
	 * @param NewThresholdParallelAngle - new value for ThresholdParallelAngle
	 */
	virtual void SetThresholdParallelAngle(float NewThresholdParallelAngle) override;

public:

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
 * Updates the rotation of the updated component.
 * @param DesiredAxisZ - desired local Z rotation axis wanted for the updated component
 * @param bRotateAroundCenter - if true, rotation happens around center of updated component
 * @param bRotateVelocity - if true and rotation happens, velocity direction is also affected
 * @return true if updated component was moved
 */
	virtual bool UpdateComponentRotation(const FVector& DesiredAxisZ, bool bRotateAroundCenter, bool bRotateVelocity) override;
	
};
	