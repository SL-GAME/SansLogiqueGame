// Fill out your copyright notice in the Description page of Project Settings.


#include "ShadowEntity_Class.h"

// Sets default values
AShadowEntity_Class::AShadowEntity_Class()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShadowEntity_Class::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShadowEntity_Class::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShadowEntity_Class::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

