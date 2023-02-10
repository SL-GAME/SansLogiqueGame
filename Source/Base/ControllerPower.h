// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerAbilityComponent.h"
#include "Components/ActorComponent.h"
#include "ControllerPower.generated.h"


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASE_API UControllerPower : public UPlayerAbilityComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UControllerPower();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
