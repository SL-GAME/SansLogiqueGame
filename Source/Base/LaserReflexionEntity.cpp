// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserReflexionEntity.h"

// Sets default values
ALaserReflexionEntity::ALaserReflexionEntity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALaserReflexionEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALaserReflexionEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

