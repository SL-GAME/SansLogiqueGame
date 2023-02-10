// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "CustomCharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

AMainCharacter::AMainCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AbilityMeshHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	AbilityMeshHand->SetupAttachment(GetFirstPersonCameraComponent());
}
