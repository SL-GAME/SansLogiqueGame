// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPCharacter.h"
#include "DummyPawn.generated.h"

UCLASS()
class BASE_API ADummyPawn : public AFPCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADummyPawn(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Dummy)
	// Called to destroy the dummy (with an effect of particle)
	void Destroying();
};
