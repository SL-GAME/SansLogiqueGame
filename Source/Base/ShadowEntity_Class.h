// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShadowEntity_Class.generated.h"

UCLASS()
class BASE_API AShadowEntity_Class : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShadowEntity_Class();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
