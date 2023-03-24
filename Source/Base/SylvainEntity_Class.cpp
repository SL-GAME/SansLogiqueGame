// Fill out your copyright notice in the Description page of Project Settings.


#include "SylvainEntity_Class.h"

// Sets default values
ASylvainEntity_Class::ASylvainEntity_Class()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASylvainEntity_Class::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASylvainEntity_Class::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASylvainEntity_Class::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

