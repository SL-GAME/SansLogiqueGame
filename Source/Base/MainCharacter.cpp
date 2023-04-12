// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "CustomCharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

AMainCharacter::AMainCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	HandBobbingComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Hand"));
	HandBobbingComponent->SetupAttachment(GetFirstPersonCameraComponent());
	HandBobbingComponent->SetRelativeLocation(FVector::ZeroVector);

	AbilityMeshHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	AbilityMeshHand->SetupAttachment(HandBobbingComponent);
}


void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float handMovementX = FMath::Clamp(-GetInputAxisValue(FName("LookRight/LookLeft")), -1.0f, 1.0f) * shiftAmount;
	float handMovementY = FMath::Clamp(GetInputAxisValue(FName("LookUp/LookDown")), -1.0f, 1.0f) * shiftAmount;

	handMovementX = FMath::Clamp(handMovementX, -maxShiftX, maxShiftX);
	handMovementY = FMath::Clamp(handMovementY, -maxShiftY, maxShiftY);

	FVector finalPos(0.0f, handMovementX, handMovementY);

	HandBobbingComponent->SetRelativeLocation(FMath::Lerp(HandBobbingComponent->GetRelativeLocation(), finalPos, FApp::GetDeltaTime() * smoothShift));

	HandBobbing();

	//UTools::PrintMessageOnScreen(FString::SanitizeFloat(test));
}

void AMainCharacter::HandBobbing() {

	if (GetCharacterMovement()->IsFalling())
		return;

	FVector newBobbing;

	if (GetVelocity().Length() > 1.0f) {

		if (bIsCrouched) {
			HandT += FApp::GetDeltaTime() * HandSpeedCrouchingBobbing;
			newBobbing = FVector(0.0f, FMath::Cos(HandT) * HandyCrouchingBobbing, FMath::Sin(HandT * 2.0f) * HandzCrouchingBobbing);
		}
		else if (bIsSprinting) {
			HandT += FApp::GetDeltaTime() * HandSpeedSprintingBobbing;
			newBobbing = FVector(0.0f, FMath::Cos(HandT) * HandySprintingBobbing, FMath::Sin(HandT * 2.0f) * HandzSprintingBobbing);
		}
		else {
			HandT += FApp::GetDeltaTime() * HandSpeedWalkingBobbing;
			newBobbing = FVector(0.0f, FMath::Cos(HandT) * HandyWalkingBobbing, FMath::Sin(HandT * 2.0f) * HandzWalkingBobbing);
		}
	}
	else {
		HandT += FApp::GetDeltaTime() * HandSpeedBreathingBobbing;
		newBobbing = FVector(0.0f, FMath::Cos(HandT) * HandyBreathingBobbing, FMath::Sin(HandT * 2.0f) * HandzBreathingBobbing);
	}

	HandBobbingComponent->SetRelativeLocation(HandBobbingComponent->GetRelativeLocation() + newBobbing);

	if (HandT > 99.0f)
		HandT = 0.0f;
}