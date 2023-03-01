// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerAbilityComponent.h"
#include "DummyAbilityComponent.generated.h"

class ADummyPawnProjectionClass;
class ADummyPawn;
/**
 * 
 */
UCLASS()
class BASE_API UDummyAbilityComponent : public UPlayerAbilityComponent
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when component is activate
	virtual void OnActivated(UActorComponent* Component, bool Reset) override;

	// Called when component is desactivate
	virtual void OnDeactivated(UActorComponent* Component) override;

public:
	// Sets default values for this component's properties
	UDummyAbilityComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called when leftAction is pressed
	virtual void LeftActionPressed() override;

	// Called when leftAction is released
	virtual void LeftActionReleased() override;

	// Called when rightAction is pressed
	virtual void RightActionPressed() override;

	// Called when rightAction is released
	virtual void RightActionReleased() override;

};
