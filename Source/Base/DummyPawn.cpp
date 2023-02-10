// Fill out your copyright notice in the Description page of Project Settings.


#include "DummyPawn.h"
#include "DummyAbilityComponent.h"
#include "CustomCharacterMovementComponent.h"

// Sets default values
ADummyPawn::ADummyPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADummyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADummyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADummyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Called to destroy the dummy (with an effect of particle)
void ADummyPawn::Destroying() {
	Destroy();
}

