// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PortalManagerComponent.generated.h"

class APortal;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASE_API UPortalManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public : 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool OnlyNearest;

protected :
	TArray<APortal*> PortalsInScene;

public:	
	// Sets default values for this component's properties
	UPortalManagerComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void UpdatePortalsInWorld();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
