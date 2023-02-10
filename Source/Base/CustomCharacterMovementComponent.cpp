// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "FPCharacter.h"
#include "Components/CapsuleComponent.h"

UCustomCharacterMovementComponent::UCustomCharacterMovementComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

}

void UCustomCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCustomCharacterMovementComponent::SetThresholdParallelAngle(float NewThresholdParallelAngle)
{
	ThresholdParallelAngle = FMath::Clamp(NewThresholdParallelAngle, 0.1f, 1.0f);

	ThresholdOrthogonalCosine = FMath::Cos(FMath::DegreesToRadians(90.0f - ThresholdParallelAngle));
	ThresholdParallelCosine = FMath::Cos(FMath::DegreesToRadians(ThresholdParallelAngle));
}


bool UCustomCharacterMovementComponent::UpdateComponentRotation(const FVector& DesiredAxisZ, bool bRotateAroundCenter, bool bRotateVelocity)
{
	//SCOPE_CYCLE_COUNTER(STAT_CharacterMovementUpdateComponentRotation);
	
	if (!HasValidData())
	{
		return false;
	}

	const FQuat PawnRotation = UpdatedComponent->GetComponentQuat();
	const FVector CurrentAxisZ = FNinjaMath::GetAxisZ(PawnRotation);

	// Abort if angle between new and old capsule 'up' axes almost equals to 0 degrees
	if (FNinjaMath::Coincident(DesiredAxisZ, CurrentAxisZ, ThresholdParallelCosine))
	{
		return false;
	}

	FVector Delta = FVector::ZeroVector;

	// Make sure actual shape isn't a sphere to calculate delta offset
	float PawnRadius, PawnHalfHeight;
	CharacterOwner->GetCapsuleComponent()->GetScaledCapsuleSize(PawnRadius, PawnHalfHeight);
	if (PawnHalfHeight > PawnRadius)
	{
		if (!bRotateAroundCenter)
		{
			// Rotate capsule around the origin of the bottom sphere
			const float SphereHeight = PawnHalfHeight - PawnRadius;
			Delta = CurrentAxisZ * (SphereHeight * -1.0f) + DesiredAxisZ * SphereHeight;
		}
		else
		{
			// Rotate capsule around the origin of the capsule, but avoid floor penetrations
			const FVector TraceStart = UpdatedComponent->GetComponentLocation();
			const float TraceDistance = PawnHalfHeight - PawnRadius;

			FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(UpdateComponentRotation), false, CharacterOwner);
			FCollisionResponseParams ResponseParam;
			InitCollisionParams(QueryParams, ResponseParam);

			FHitResult Hit(1.0f);
			const bool bBlockingHit = FloorSweepTest(Hit, TraceStart, TraceStart - DesiredAxisZ * TraceDistance,
				UpdatedComponent->GetCollisionObjectType(), FCollisionShape::MakeSphere(PawnRadius), QueryParams, ResponseParam);
			if (bBlockingHit)
			{
				const float AvgFloorDist = (MIN_FLOOR_DIST + MAX_FLOOR_DIST) * 0.5f;
				Delta = DesiredAxisZ * (TraceDistance * (1.0f - Hit.Time) + AvgFloorDist);
			}
		}
	}

	// Take desired Z rotation axis of capsule, try to keep current X rotation axis of capsule
	const FQuat NewRotation = FNinjaMath::MakeFromZQuat(DesiredAxisZ, PawnRotation, ThresholdParallelCosine);
	const FQuat SmoothRotation = FQuat::Slerp(PawnRotation, NewRotation,SmoothRate);
	// Try to rotate the capsule now, but don't sweep because penetrations are handled properly
	FHitResult Hit(1.0f);

	UCameraComponent* camera = Cast<AFPCharacter>(GetOwner())->GetFirstPersonCameraComponent();
	FRotator CamRot = camera->GetRelativeRotation();

	bool bMoveResult;
	if (UseSmoothRotation) 
		bMoveResult = SafeMoveUpdatedComponent(Delta, SmoothRotation, false, Hit, ETeleportType::TeleportPhysics);
	else
		bMoveResult = SafeMoveUpdatedComponent(Delta, NewRotation, false, Hit, ETeleportType::TeleportPhysics);

	if (bMoveResult && bRotateVelocity && !Velocity.IsZero())
	{
		// Modify Velocity direction to prevent losing speed on rotation change
		Velocity = FQuat::FindBetweenNormals(CurrentAxisZ, DesiredAxisZ).RotateVector(Velocity);
	}

	return bMoveResult;
}