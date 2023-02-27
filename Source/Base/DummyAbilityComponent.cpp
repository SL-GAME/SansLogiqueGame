// Fill out your copyright notice in the Description page of Project Settings.


#include "DummyAbilityComponent.h"
#include "DummyPawnProjectionClass.h"
#include "MainCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "DummyPawn.h"
#include "NonPosableInterface.h"
#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UDummyAbilityComponent::UDummyAbilityComponent() : Super()
{

}

// Called when the game starts or when spawned
void UDummyAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called when component is activate
void UDummyAbilityComponent::OnActivated(UActorComponent* Component, bool Reset)
{
	Super::OnActivated(Component, Reset);
}

// Called when component is desactivate
void UDummyAbilityComponent::OnDeactivated(UActorComponent* Component)
{
	Super::OnDeactivated(Component);
}

// Called every frame
void UDummyAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// Called when leftAction is pressed
void UDummyAbilityComponent::LeftActionPressed()
{
	Super::LeftActionPressed();
}

// Called when leftAction is released
void UDummyAbilityComponent::LeftActionReleased()
{
	Super::LeftActionReleased();
}

// Called when rightAction is pressed
void UDummyAbilityComponent::RightActionPressed()
{
	Super::RightActionPressed();
}


// Called when rightAction is released
void UDummyAbilityComponent::RightActionReleased()
{
	Super::RightActionReleased();
}


